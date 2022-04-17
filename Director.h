#pragma once
#include <string>
#include <regex>
using std::string;
class Director
{
    private:
        string directorId;
        string directorName;

    public:
        Director();
        Director(string directorId, string directorName);

        string GetId();
        string GetName();

        void ReadInput(string currentLine);

};