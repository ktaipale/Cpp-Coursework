#include "project.hh"
#include <iostream>

Project::Project(const std::string& id, const std::string& start):
    id_(id), start_(start)
{
}

Project::Project(const std::string& id, const Date &start):
    id_(id), start_(start)
{
}

Project::~Project()
{
    //std::cout << "Project " << id_ << " destructed." << std::endl;
}

std::string Project::getID()
{
    return id_;
}

Date Project::getStart()
{
    return start_;
}

Date Project::getEnd()
{
    return end_;
}

void Project::printStart()
{
    start_.print();
}

void Project::addRequirement(const std::string &requirement)
{
    requirements_.push_back(requirement);
    hasRequirements = true;
}

bool Project::checkRequirements()
{
    return hasRequirements;
}

std::vector<std::string> Project::getRequirements()
{
    return requirements_;
}

void Project::addWorkers(const std::string &worker)
{
    workers_.push_back(worker);
}

std::vector<std::string> Project::getWorkers()
{
    return workers_;
}

void Project::updateWorkers(std::vector<std::string> workers)
{
    workers_.clear();
    workers_ = workers;
}

void Project::printEnd()
{
    end_.print();
}

void Project::endProject(const Date &end)
{
    end_ = end;
}
