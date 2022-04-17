#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include "Director.h"
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::getline;

class Movie
{
    private:
        string titleId;
        string movieTitle;
        vector<string> directors;
        vector<string> genres;
        float averageRating;
        float similarityScore;

        void copyData(const Movie& other);  //for copy constructor & copy assignment

        //subfunctions for ReadInput
    public:
        //constructors
        Movie();
        Movie(string titleId, string movieTitle, vector<string> directors, vector<string> genres, float averageRating, float similarityScore);
        Movie(string titleId, string movieTitle, float similarityScore);    //thought it might be useful, can delete if unused

        //big three
        ~Movie();                   //removed the dynamic memory alloc, but keep it here just in case
        Movie(const Movie& other);
        const Movie& operator=(const Movie& other);

        //operator overload
        bool operator<(const Movie& other);
        bool operator>(const Movie& other);
        bool operator==(const Movie& other);

        //accessors
        string GetId();
        string GetTitle();
        vector<string>& GetDirectors();
        vector<string>& GetGenres();
        float GetRating();
        float GetSimilarity();

        //behaviors
        void DetermineSimilarity(const Movie& toCompare);
        void ReadTitleBasics(string currentLine); //title, format, genres
        void ReadTitleCrew(string directorIdList, std::unordered_map<string,Director>& directorList);
        void ReadTitleRatings(string stringRating);
        void Print();
        void PrintCondensed();
};