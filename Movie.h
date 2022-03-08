#include <string>
using std::string;
class Movie
{
    private:
        string titleId;
        string movieTitle;
        string* directors;
        string* genres;
        float averageRating;
        float similarityScore;

        void copyData(const Movie& other);  //for copy constructor & copy assignment

    public:
        //constructors
        Movie();
        Movie(string titleId, string movieTitle, string* directors, string* genres, float averageRating, float similarityScore);
        Movie(string titleId, string movieTitle, float similarityScore);    //thought it might be useful, can delete if unused

        //big three
        ~Movie();
        Movie(const Movie& other);
        const Movie& operator=(const Movie& other);

        //operator overload
        bool operator<(const Movie& other);
        bool operator>(const Movie& other);
        bool operator==(const Movie& other);

        //accessors
        string GetId();
        string GetTitle();
        string* GetDirectors();
        string* GetGenres();
        float GetRating();

        //similarity score function
        void determineSimilarity(const Movie& toCompare);
};