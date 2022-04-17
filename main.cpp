#include <iostream>
#include <unordered_map>
#include "Heap.h"
using namespace std;

void ReadData(unordered_map<string, Movie>& movies, unordered_map<string, Director>& directors)
{
   string inputName = ""; //user's input name
    Movie* sourceMovie;

    //read movies
    ifstream input("datasets/title_basics.tsv");
    string currentLine;


    //for(int i = 0; i < 5; i++)
    while(getline(input, currentLine))
    {
      // getline(input, currentLine);
        Movie newMovie;
        newMovie.ReadTitleBasics(currentLine);
        if(inputName == newMovie.GetTitle())
            sourceMovie = &newMovie;
        
        movies[newMovie.GetId()] = newMovie;
    }
    
    input.close();

    //read directors
    input.open("datasets/name_basics.tsv");
    while(getline(input, currentLine))
    {
        Director newDirector;
        newDirector.ReadInput(currentLine);
        directors[newDirector.GetId()] = newDirector;
    }

    input.close();


    //read crew
    input.open("datasets/title_crew.tsv");
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
    inputTitle.open("datasets/title_ratings.tsv");
     //for(int i = 0; i < 5; i++)
     while(getline(inputTitle, currentLine))
    {
        //getline(inputTitle, currentLine);

        //tab separate values
        std::regex rgx("\t");
        std::sregex_token_iterator iter(currentLine.begin(), currentLine.end(), rgx, -1);
        string id = *iter;
        iter++;
        string stringRating = *iter;

        movies[id].ReadTitleRatings(stringRating);


    }


    inputTitle.close();
}

int main()
{
    unordered_map<string, Movie> movies;
    unordered_map<string, Director> directors;
    ReadData(movies, directors);
     movies["tt2527338"].Print();

   
}

