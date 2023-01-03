#include "DataManager.hpp"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

std::string DataManager::RegisterUser(std::vector<std::string> splittedMessage)
{
    if (splittedMessage.size() != 5)
    {
        std::cout << REG_INVALID_DATA_MESSAGE << std::endl;
        return REG_INVALID_DATA_CODE;
    }

    if (!IsValidEmail(splittedMessage[1]))
    {
        std::cout << REG_INVALID_EMAIL_MESSAGE << std::endl;
        return REG_INVALID_EMAIL_CODE;
    }
    if (EmailExists(splittedMessage[1]))
    {
        std::cout << REG_EMAIL_EXISTS_MESSAGE << std::endl;
        return REG_EMAIL_EXISTS_CODE;
    }
    if (!IsSecurePassword(splittedMessage[2]))
    {
        std::cout << REG_INSECURE_PASS_MESSAGE << std::endl;
        return REG_INSECURE_PASS_CODE;
    }
    if (!IsValidName(splittedMessage[3]))
    {
        std::cout << REG_INVALID_NAME_MESSAGE << std::endl;
        return REG_INVALID_NAME_CODE;
    }
    if (!IsValidUserType(splittedMessage[4]))
    {
        std::cout << REG_INVALID_USERTYPE_MESSAGE << std::endl;
        return REG_INVALID_USERTYPE_CODE;
    }

    sqlite3pp::database db(DATABASE_PATH);

    sqlite3pp::command query(
        db, "INSERT INTO Users (ID, Email, Password, Name, UserType) VALUES (?, ?, ?, ?, ?)");
    query.binder() << UUIDGenerator::Generate(UUID_PREFIX_USER)
                   << splittedMessage[1]
                   << splittedMessage[2]
                   << splittedMessage[3]
                   << splittedMessage[4];
    query.execute();

    std::cout << REG_SUCCESS_MESSAGE << std::endl;
    return REG_SUCCESS_CODE;
}

bool DataManager::IsValidName(std::string name)
{
    if (name.empty())
    {

        return false;
    }
    if (std::find_if(name.begin(), name.end(), ::isdigit) != name.end())
    {

        return false;
    }
    return true;
}

bool DataManager::IsSecurePassword(std::string password)
{
    if (password.size() < 7)
    {
        return false;
    }
    if (std::find_if(password.begin(), password.end(), ::isdigit) == password.end())
    {
        return false;
    }

    return true;
}

// nume@yahoo.com
// nume.nume@yahoocom
// string@string.string regex

bool DataManager::IsValidEmail(std::string email)
{
    if (email.find("@") == std::string::npos)
    {
        return false;
    }
    if (email.find(".") == std::string::npos)
    {
        return false;
    }
    return true;
}
bool DataManager::EmailExists(std::string email)
{
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Email FROM Users");

    for (sqlite3pp::query::iterator k = qry.begin(); k != qry.end(); ++k)
    {

        std::string dbEmailReg = (*k).get<std::string>(0);

        if (email == dbEmailReg)
        {
            return true;
        }
    }
    return false;
}

bool DataManager::IsValidUserType(std::string userType)
{
    if (userType == "0" || userType == "1")
    {
        return true;
    }
    return false;
}

std::string DataManager::LoginUser(std::vector<std::string> splittedMessage)
{
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Email,Password,UserType FROM Users");

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {
        std::string dbEmail, dbPassword, userType;

        for (int j = 0; j < qry.column_count(); ++j)
        {
            if (j == 0)
            {
                dbEmail = (*i).get<char const *>(j);
            }
            if (j == 1)
            {
                dbPassword = (*i).get<char const *>(j);
            }
        }
        std::string clEmail, clPassword;

        clEmail = splittedMessage[1];
        clPassword = splittedMessage[2];

        if (clEmail == dbEmail && clPassword == dbPassword)
        {
            std::cout << LOGIN_SUCCESS_MESSAGE << std::endl;
            std::string message = LOGIN_SUCCESS_CODE "," + userType;
            return LOGIN_SUCCESS_CODE;
        }
    }

    std::cout << LOGIN_USER_PASS_INCORECT_MESSAGE << std::endl;
    return LOGIN_USER_PASS_INCORECT_CODE;
}

std::string DataManager::GetUserType(std::string email)
{
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Email,UserType FROM Users");

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {
        std::string dbEmail, dbUserType;
        for (int j = 0; j < qry.column_count(); ++j)
        {
            if (j == 0)
            {
                dbEmail = (*i).get<char const *>(j);
            }
            if (j == 1)
            {
                dbUserType = (*i).get<char const *>(j);
            }
        }
        if (email == dbEmail)
        {
            return dbUserType;
        }
    }
    return "0";
}

std::string DataManager::SearchActor(std::string actorName)
{
    std::transform(actorName.begin(), actorName.end(), actorName.begin(), ::toupper);

    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT * FROM Actors");

    std::string allActors;

    // Momentan, se afiseaza doar numele actorilor gasiti
    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {
        std::string currentActorId = (*i).get<char const *>(0);
        std::string currentActorName = (*i).get<char const *>(1);

        std::transform(currentActorName.begin(), currentActorName.end(), currentActorName.begin(), ::toupper);

        if (currentActorName.find(actorName) != std::string::npos)
        {
            allActors += "ID: " + currentActorId + "\tName: " + currentActorName + "\n";
        }
    }

    if (allActors.empty())
    {
        allActors = "No actors found with name: " + actorName;
    }
    return allActors;
}

std::string DataManager::SearchDirector(std::string directorName)
{
    std::transform(directorName.begin(), directorName.end(), directorName.begin(), ::toupper);
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Name FROM Directors");

    std::string allDirectors;

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {
        std::string currentDirectorId = (*i).get<char const *>(0);
        std::string currentDirectorName = (*i).get<char const *>(1);

        std::transform(currentDirectorName.begin(), currentDirectorName.end(), currentDirectorName.begin(), ::toupper);

        if (currentDirectorName.find(directorName) != std::string::npos)
        {
            allDirectors += "ID: " + currentDirectorId + "\tName: " + currentDirectorName + "\n";
        }
    }

    if (allDirectors.empty())
    {
        allDirectors = "No directors found with name: " + directorName;
    }
    return allDirectors;
}

std::string DataManager::SearchMovie(std::string movieName)
{
    std::transform(movieName.begin(), movieName.end(), movieName.begin(), ::toupper);
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT * FROM Movies");

    std::string allMovies;

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {
        std::string currentMovieName = (*i).get<char const *>(1);

        std::transform(currentMovieName.begin(), currentMovieName.end(), currentMovieName.begin(), ::toupper);

        if (currentMovieName.find(movieName) != std::string::npos)
        {
            std::string currentMovieId = (*i).get<char const *>(0);
            std::string currentMovieReleaseDate = (*i).get<char const *>(2);
            std::string currentMovieCategory = (*i).get<char const *>(3);
            allMovies += "ID: " + currentMovieId + "\tName: " + currentMovieName + "\tRelease Date: " + currentMovieReleaseDate + "\tCategory: " + currentMovieCategory + "\n";
        }
    }

    if (allMovies.empty())
    {
        allMovies = "No movies found with name: " + movieName;
    }
    return allMovies;
}

std::string DataManager::ActorAdd(std::string actorName)
{
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::command query(db, "INSERT INTO Actors (ID, Name) VALUES (?, ?)");
    query.binder() << UUIDGenerator::Generate(UUID_PREFIX_ACTOR)
                   << actorName;
    query.execute();

    return ACTOR_ADD_SUCCESS_MESSAGE;
}

std::string DataManager::DirectorAdd(std::string directorName)
{
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::command query(
        db, "INSERT INTO Directors (ID, Name) VALUES (?, ?)");

    query.binder() << UUIDGenerator::Generate(UUID_PREFIX_DIRECTOR)
                   << directorName;
    query.execute();

    return DIRECTOR_ADD_SUCCES_MESSAGE;
}

std::string DataManager::MovieAdd(std::vector<std::string> splittedMessage)
{

    std::string movieName = splittedMessage[1];
    std::string releaseDate = splittedMessage[2];
    std::string category = splittedMessage[3];
    sqlite3pp::database db(DATABASE_PATH);

    sqlite3pp::command queryCategories(
        db, "INSERT INTO Categories (Name) VALUES (?)");
    queryCategories.binder()
        << category;

    queryCategories.execute();

    sqlite3pp::command queryMovies(
        db, "INSERT INTO Movies (ID, Name, ReleaseDate, Category) VALUES (?, ?, ?, ?)");
    queryMovies.binder() << UUIDGenerator::Generate(UUID_PREFIX_MOVIE)
                         << movieName
                         << releaseDate
                         << category;

    queryMovies.execute();
    return MOVIE_ADD_SUCCES_MESSAGE;
}

std::string DataManager::DeleteActor(std::string deleteActor)
{
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT ID FROM Actors");

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {
        std::string dbId;
        for (int j = 0; j < qry.column_count(); ++j)
        {
            if (j == 0)
            {
                dbId = (*i).get<char const *>(j);
            }
        }
        if (deleteActor == dbId)
        {
            sqlite3pp::database db(DATABASE_PATH);
            sqlite3pp::query qry(db, "DELETE FROM Actors WHERE ID values (?)");
        }
    }

    return "0";

    SELECT *FROM Actors WHERE ID = 'actor_123';

    cate rezultate am avut la select->0 sau 1

        if (rezultate == 1)
    {
        DELETE FROM Actors WHERE ID = 'actor_123';
        sendMessage("Am sters actorul cu id-ul " + actor_id)
    }
    else
    {
        sendMessage("Actorul cu id-ul " + actor_id + " nu se gaseste in baza de date, deci nu am avut ce sa sterg")
    }
}
