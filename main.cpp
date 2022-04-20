#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <chrono>
#include "Heap.h"
using namespace std;

Movie* ReadData(string userInput, unordered_map<string, Movie>& movies, unordered_map<string, Director>& directors)
{
    //read movies
    ifstream input("../datasets/title_basics.tsv");
    string currentLine;

    int lineCounter = 0;
    cout << "Current file and line:" << endl;
    while(getline(input, currentLine))
    {
        Movie newMovie;
        newMovie.ReadTitleBasics(currentLine);

        cout << '\r' << "title_basics.tsv, " << lineCounter;
        lineCounter++;

        movies[newMovie.GetId()] = newMovie;
    }
    
    input.close();
    lineCounter = 0;
    cout << '\r' << "                                    ";

    //read directors
    input.open("../datasets/name_basics.tsv");
    while(getline(input, currentLine))
    {
        Director newDirector;
        newDirector.ReadInput(currentLine);

        cout << '\r' << "name_basics.tsv, " << lineCounter;
        lineCounter++;

        directors[newDirector.GetId()] = newDirector;
    }

    input.close();

    lineCounter = 0;
    cout << '\r' << "                                    ";

    //read crew
    input.open("../datasets/title_crew.tsv");
    while(getline(input, currentLine))
    {
        //tab separate values
        std::regex rgx("\t");
        std::sregex_token_iterator iter(currentLine.begin(), currentLine.end(), rgx, -1);
        string id = *iter;
        iter++;
        string directorIdList = *iter;

        cout << '\r' << "title_crew.tsv, " << lineCounter;
        lineCounter++;

        movies[id].ReadTitleCrew(directorIdList, directors);

    }

    input.close();

    ifstream inputTitle;
    inputTitle.open("../datasets/title_ratings.tsv");

    lineCounter = 0;
    cout << '\r' << "                                    ";

    while(getline(inputTitle, currentLine))
    {

        //tab separate values
        std::regex rgx("\t");
        std::sregex_token_iterator iter(currentLine.begin(), currentLine.end(), rgx, -1);
        string id = *iter;
        iter++;
        string stringRating = *iter;

        cout << '\r' << "title_ratings.tsv, " << lineCounter;
        lineCounter++;

        movies[id].ReadTitleRatings(stringRating);

    }

    cout << '\r' << "Complete!                          " << endl << endl;

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

    //Starts a timer to measure time spend on heap
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
    cout << endl << "Operation time was " << duration.count() << " ms." << endl;
    
    //TODO: Add stuff from red-black/binary tree data structire
   
}

