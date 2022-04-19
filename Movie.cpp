#include "Movie.h"

//========================= CONSTRUCTORS =============================================
Movie::Movie()
{
    titleId = "no ID set";
    movieTitle = "no title set";
    averageRating = -1;
    similarityScore = 0;
}

Movie::Movie(string titleId, string movieTitle, vector<string> directors, vector<string> genres, float averageRating, float similarityScore)
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
vector<string>& Movie::GetGenres()
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
void Movie::DetermineSimilarity(const Movie& toCompare)
{

    //Uses set_intersection to scrub both vectors and generate new vectors with only
    //the directors and genres they have in common.
    vector<string> inCommonDirectors;
    vector<string> inCommonGenres;
    std::set_intersection(this->directors.begin(), this->directors.end(), toCompare.directors.begin(), toCompare.directors.end(), std::back_inserter(inCommonDirectors));
    std::set_intersection(this->genres.begin(), this->genres.end(), toCompare.genres.begin(), toCompare.genres.end(), std::back_inserter(inCommonGenres));

    similarityScore = averageRating * ((float)inCommonDirectors.size() + (float)inCommonGenres.size());
}




void Movie::ReadTitleBasics(string currentLine)
{
    
    //tab separate values
    std::regex rgx("\t");

    //iterator for each tab separated value
    std::sregex_token_iterator iter(currentLine.begin(), currentLine.end(), rgx, -1);
    
    titleId = *iter;
    iter++;
    iter++;
    movieTitle = *iter;
    iter++;
    iter++;
    iter++;
    iter++;
    iter++;
    iter++;
    string genreList = *iter;
    
    //comma separated genres
    if(genreList != "\\N")
    {

        /* BROKEN !!! NEEDS FIXING */
        std::regex comma(",");
        std::sregex_token_iterator iter2(genreList.begin(), genreList.end(), comma, -1);
        std::sregex_token_iterator end;
        for(; iter2 != end; iter2++)
            genres.push_back(*iter);
          
        
    }

    //Sort genre vector for easier calculation in the similarity score function
    //later on.
    std::sort(genres.begin(), genres.end());

}

void Movie::ReadTitleCrew(string directorIdList, std::unordered_map<string,Director>& directorList)
{
    //comma separated directors
    std::regex comma(",");
    std::sregex_token_iterator iter2(directorIdList.begin(), directorIdList.end(), comma, -1);
    std::sregex_token_iterator end;

    for(; iter2 != end; iter2++)
    {
        directors.push_back(directorList[*iter2].GetName());
    }

    //Sort vector of directors for easier calculation in the similarity score function
    //later on.
    std::sort(directors.begin(), directors.end());
}

void Movie::ReadTitleRatings(string stringRating)
{
    averageRating = std::stof(stringRating);
}


void Movie::Print()
{
    cout << "Title ID: " << titleId << endl;
    cout << "Title: " << movieTitle << endl;
    cout << "Genres: ";
    for(string s : genres)
    {
        cout << s << ", ";
    }
    cout << endl;

    cout << "Directors: ";
    for(string s : directors)
        cout << s << ", ";
    cout << endl;
    cout << "Average Rating: " << averageRating << endl;
    cout << "Similarity Score: " << similarityScore << endl;

}

void Movie::PrintCondensed()
{
    cout << "id: " << titleId << " | title: " << movieTitle << " | similarity: " << similarityScore << endl;
}


//============================ PRIVATE FUNCTIONS ==========================================
void Movie::copyData(const Movie& other)
{
    titleId = other.titleId;
    movieTitle = other.movieTitle;
    averageRating = other.averageRating;
    similarityScore = other.similarityScore;

    directors = other.directors;
    genres = other.genres;    

}

