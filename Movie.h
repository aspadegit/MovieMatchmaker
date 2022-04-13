#include <string>
#include <vector>
using std::vector;
using std::string;
class Movie
{
    private:
        string titleId;
        string movieTitle;
        vector<string> directors;
        string genres[3];
        float averageRating;
        float similarityScore;

        void copyData(const Movie& other);  //for copy constructor & copy assignment

    public:
        //constructors
        Movie();
        Movie(string titleId, string movieTitle, vector<string> directors, string* genres, float averageRating, float similarityScore);
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
        string* GetGenres();
        float GetRating();
        float GetSimilarity();

        //similarity score function
        void determineSimilarity(const Movie& toCompare);
};