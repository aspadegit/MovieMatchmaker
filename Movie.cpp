#include "Movie.h"

//========================= CONSTRUCTORS =============================================
Movie::Movie()
{
    titleId = "no ID set";
    movieTitle = "no title set";
    string* directors = nullptr;
    string* genres = new string[3]; //there will be 3 genres
    float averageRating = -1;
    float similarityScore = 0;
}

Movie::Movie(string titleId, string movieTitle, string* directors, string* genres, float averageRating, float similarityScore)
{
    this->titleId = titleId;
    this->movieTitle = movieTitle;
    this->directors = directors;
    this->genres = genres;
    this->averageRating = averageRating;
    this->similarityScore = similarityScore;
}
        
Movie::Movie(string titleId, string movieTitle, float similarityScore)
{
    this->titleId = titleId;
    this->movieTitle = movieTitle;
    string* directors = nullptr;
    string* genres = new string[3]; //there will be 3 genres
    float averageRating = -1;
    this->similarityScore = similarityScore;

}

//============================ BIG THREE ==================================================
Movie::~Movie()
{
    delete[] directors;
    delete[] genres;
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
string* Movie::GetDirectors()
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

    directors = new string[other.directors->length()];

    for(int i = 0; i < other.directors->length(); i++)
    {
        directors[i] = other.directors[i];
    }

    for(int i = 0; i < 3; i++)
    {
        genres[i] = other.genres[i];
    }
    

}
