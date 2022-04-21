#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <chrono>
#include "Heap.h"
#include "MergeSort.h"
using namespace std;

Movie* ReadData(string userInput, unordered_map<string, Movie>& movies, unordered_map<string, Director>& directors)
{
    //read movies
    ifstream input("../smalldatasets/title_basics.tsv");
    string currentLine;

    while(getline(input, currentLine))
    {
        Movie newMovie;
        newMovie.ReadTitleBasics(currentLine);
        movies[newMovie.GetId()] = newMovie;
    }
    
    input.close();

    //read directors
    input.open("../smalldatasets/name_basics.tsv");
    while(getline(input, currentLine))
    {
        Director newDirector;
        newDirector.ReadInput(currentLine);
        directors[newDirector.GetId()] = newDirector;
    }

    input.close();

    //read crew
    input.open("../smalldatasets/title_crew.tsv");
    while(getline(input, currentLine))
    {
        //tab separate values
        std::regex rgx("\t");
        std::sregex_token_iterator iter(currentLine.begin(), currentLine.end(), rgx, -1);
        string id = *iter;
        iter++;
        string directorIdList = *iter;

        movies[id].ReadTitleCrew(directorIdList, directors);

    }

    input.close();

    ifstream inputTitle;
    inputTitle.open("../smalldatasets/title_ratings.tsv");

    while(getline(inputTitle, currentLine))
    {

        //tab separate values
        std::regex rgx("\t");
        std::sregex_token_iterator iter(currentLine.begin(), currentLine.end(), rgx, -1);
        string id = *iter;
        iter++;
        string stringRating = *iter;

        movies[id].ReadTitleRatings(stringRating);

    }

    inputTitle.close();
    for (auto i = movies.begin(); i != movies.end(); i++)
    {
        if (i->second.GetTitle() == userInput)
            return &(i->second);
    }
    return new Movie();
}

int main()
{

    std::cout << "Enter movie title: ";
    string userInput = "";
    getline(cin, userInput);

    unordered_map<string, Movie> movies;
    unordered_map<string, Director> directors;

    cout << endl << "Reading data from databases..." << endl << endl;
    Movie* inputMovie = ReadData(userInput, movies, directors);
    
    if (inputMovie->GetId() == "no ID set") {
        cout << "Requested movie does not exist in database. Check your directories or spelling." << endl << endl;
        return 0;
    }

    for (auto i = movies.begin(); i != movies.end(); i++)
    {
        i->second.DetermineSimilarity(*inputMovie);
    }

    //Starts a timer to measure time spent on heap
    cout << "Running heap test..." << endl;
    auto start = chrono::high_resolution_clock::now();

    Heap* heap = new Heap();
    for (auto i = movies.begin(); i != movies.end(); i++)
    {
        heap->Insert(i->second);
    }

    cout << endl << "~~~Heap Data Structure Test~~~" << endl;

    cout << endl << "Recommended Movies and their Similarity Scores: " << endl << endl;
    for (int i = 0; i < 10; i++) 
    {
        Movie heapTop = heap->ExtractMax();

        //Checks for identical movie.
        if (heapTop.GetTitle() == userInput) {
            i--;
            continue;
        }

        cout << '\"' << heapTop.GetTitle() << '\"' << ", ";
        cout << fixed << setprecision(2) << heapTop.GetSimilarity() << endl;
    }

    //Calculates time spend on heap insertion/access
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << endl << "Operation time was " << duration.count() << " ms." << endl << endl;
    
    //Starts a timer to measure time spent on mergesort
    cout << "Running mergesort test..." << endl;
    start = chrono::high_resolution_clock::now();

    Movie *arr = new Movie[movies.size()];

    int index = 0;
    for (auto i = movies.begin(); i != movies.end(); i++)
    {
        arr[index] = i->second;
        index++;
    }

    MergeSort(arr, 0, index);

    cout << endl << "~~~MergeSort Algorithm Test~~~" << endl;

    cout << endl << "Recommended Movies and their Similarity Scores: " << endl << endl;

    int printMovies = 10;
    for (int i = 0; i < printMovies; i++)
    {
        Movie similarMovie = arr[i];

        //Checks for identical movie to user input.
        if (similarMovie.GetTitle() == userInput) {
            printMovies++;
            continue;
        }

        cout << '\"' << similarMovie.GetTitle() << '\"' << ", ";
        cout << fixed << setprecision(2) << similarMovie.GetSimilarity() << endl;
    }
    delete[] arr;
    //Calculates time spend on mergesort algorithm
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << endl << "Operation time was " << duration.count() << " ms." << endl << endl;
}

