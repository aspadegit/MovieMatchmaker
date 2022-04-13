#include "Movie.h"

//========================= CONSTRUCTORS =============================================
Movie::Movie()
{
    titleId = "no ID set";
    movieTitle = "no title set";
    averageRating = -1;
    similarityScore = 0;
}

Movie::Movie(string titleId, string movieTitle, vector<string> directors, string* genres, float averageRating, float similarityScore)
{
    this->titleId = titleId;
    this->movieTitle = movieTitle;
    this->directors = directors;
    for(int i = 0; i < 3; i++)
    {
        this->genres[i] = genres[i];
    }
    this->averageRating = averageRating;
    this->similarityScore = similarityScore;
}
        
Movie::Movie(string titleId, string movieTitle, float similarityScore)
{
    this->titleId = titleId;
    this->movieTitle = movieTitle;
    float averageRating = -1;
    this->similarityScore = similarityScore;

}

//============================ BIG THREE ==================================================
Movie::~Movie()
{
}
Movie::Movie(const Movie& other)
{
    copyData(other);
}
const Movie& Movie::operator=(const Movie& other)
{
    copyData(other);
    return *this;
}


//============================ OPERATORS ==================================================
bool Movie::operator<(const Movie& other)
{
    return titleId < other.titleId;
}
bool Movie::operator>(const Movie& other)
{
    return titleId > other.titleId;
}
bool Movie::operator==(const Movie& other)
{
    return titleId == other.titleId;
}


//============================ ACCESSORS ==================================================
string Movie::GetId()
{
    return titleId;
}
string Movie::GetTitle()
{
    return movieTitle;
}
vector<string>& Movie::GetDirectors()
{
    return directors;
}
string* Movie::GetGenres()
{
    return genres;
}
float Movie::GetRating()
{
    return averageRating;
}
float Movie::GetSimilarity()
{
    return similarityScore;
}


//============================ BEHAVIORS ==================================================
void Movie::determineSimilarity(const Movie& toCompare)
{
    //TODO: implement this
}


//============================ PRIVATE FUNCTIONS ==========================================
void Movie::copyData(const Movie& other)
{
    titleId = other.titleId;
    movieTitle = other.movieTitle;
    averageRating = other.averageRating;
    similarityScore = other.similarityScore;

    directors = other.directors;

    for(int i = 0; i < 3; i++)
    {
        genres[i] = other.genres[i];
    }
    

}
