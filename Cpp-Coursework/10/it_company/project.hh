/* Class Project
 * ----------
 * COMP.CS.110 FALL 2023
 * ----------
 * Class for describing a project in an IT company.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef PROJECT_HH
#define PROJECT_HH

#include "employee.hh"
#include "date.hh"
#include "utils.hh"
#include <string>

const std::string NOT_QUALIFIED = "Not qualified any more: ";

class Project
{
public:
    /**
     * @brief Project constructor
     * @param : id
     * @param : start (given as string ddmmyyyy)
     */
    Project(const std::string& id, const std::string& start);

    /**
     * @brief Project constructor
     * @param : id
     * @param : start (given as Date object)
     */
    Project(const std::string& id, const Date& start);

    /**
     * @brief Project destructor
     */
    ~Project();

    // More public methods
    std::string getID();
    Date getStart();
    Date getEnd();
    void endProject(const Date &start);
    void printEnd();
    void printStart();

    void addRequirement(const std::string &requirement);
    bool checkRequirements();
    std::vector<std::string> getRequirements();

    void addWorkers(const std::string &worker);
    std::vector<std::string> getWorkers();
    void updateWorkers(std::vector<std::string> workers);

private:
    /**
     * @brief obvious attributes
     */
    std::string id_; // Can be a name or any other identifier
    Date start_;
    Date end_;
    std::vector<std::string> requirements_;
    std::vector<std::string> workers_;
    bool hasRequirements = false;

    // More attributes and private methods
};

#endif // PROJECT_HH
