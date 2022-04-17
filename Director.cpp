#include "Director.h"

Director::Director()
{
    directorId = "No director ID set";
    directorName = "No director name set";
}

Director::Director(string directorId, string directorName)
{
    this->directorId = directorId;
    this->directorName = directorName;
}

string Director::GetId()
{
    return directorId;
}

string Director::GetName()
{
    return directorName;
}


void Director::ReadInput(string currentLine)
{
    //tab separate values
    std::regex rgx("\t");

    //iterator for each tab separated value
    std::sregex_token_iterator iter(currentLine.begin(), currentLine.end(), rgx, -1);
    
    directorId = *iter;
    iter++;
    directorName = *iter;
    
}