#include "company.hh"
#include "utils.hh"
#include <iostream>
#include <set>
#include <algorithm>

Company::Company()
{
}

Company::~Company()
{
    // Poistetaan pointterit ohjelman lopettaessa toimintansa
    for ( auto allStaff : all_staff_)
    {
        delete allStaff.second;
    }
    for ( auto project : projects_)
    {
        delete project.second;
    }
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja asettaa ohjelman päivämäärän syötteen mukaan.
void Company::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not Utils::is_numeric(day, false) or
        not Utils::is_numeric(month, false) or
        not Utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    Utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    Utils::today.print();
    std::cout << std::endl;
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja liikkuu päivämäärissä annetun määrän eteen päin.
void Company::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not Utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    Utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    Utils::today.print();
    std::cout << std::endl;
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja lisää siitä luetun henkilön yrityksen työntekijäksi.
void Company::recruit(Params params)
{
    std::string employee_id = params.at(0);
    std::map<std::string, Employee*>::const_iterator
            iter = current_staff_.find(employee_id);

    if( iter != current_staff_.end() )
    {
        std::cout << ALREADY_EXISTS << employee_id << std::endl;
        return;
    }

    iter = all_staff_.find(employee_id);
    if( iter != all_staff_.end() )
    {
        current_staff_.insert(*iter);
        std::cout << EMPLOYEE_RECRUITED << std::endl;
        return;
    }

    Employee* new_employee = new Employee(employee_id);
    all_staff_.insert({employee_id, new_employee});
    current_staff_.insert({employee_id, new_employee});
    std::cout << EMPLOYEE_RECRUITED << std::endl;
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja poistaa siitä saadun henkilön yrityksen nykyisistä työntekijöistä.
void Company::leave(Params params)
{
    std::string employee_id = params.at(0);
    std::map<std::string, Employee*>::const_iterator
            iter = current_staff_.find(employee_id);
    if( iter == current_staff_.end() )
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    current_staff_.erase(iter); // Employee still stays in all_staff_
    std::cout << EMPLOYEE_LEFT << std::endl;
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja lisää annetulle henkilölle annetun taidon.
void Company::add_skill(Params params)
{
    std::string employee_id = params.at(0);
    std::string skill_name = params.at(1);

    std::map<std::string, Employee*>::const_iterator
            staff_iter = current_staff_.find(employee_id);
    if( staff_iter == current_staff_.end() )
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    staff_iter->second->add_skill(skill_name);
    std::cout << SKILL_ADDED << employee_id << std::endl;
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja tulostaa yrityksen nykyisen henkilöstön.
void Company::print_current_staff(Params)
{
    if( current_staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    for( auto employee : current_staff_ )
    {
        employee.second->print_id("");
        std::cout << std::endl;
    }
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja luo uuden projektin annetulla nimellä.
void Company::create_project(Params params)
{
    std::string projectName = params.at(0);
    if (projects_.find(projectName) != projects_.end())
    {
        std::cout << ALREADY_EXISTS << projectName << std::endl;
        return;
    }
    else
    {
        std::cout << PROJECT_CREATED << std::endl;
    }

    // Projektin tiedot lisätään eri tietosäiliöihin
    // muiden funktioiden tulostuksia varten.
    Project* project = new Project(projectName, Utils::today);
    projects_.insert({project->getID(), project});
    projectOrder_.push_back(project->getID());
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja sulkee käynnissä olevan projektin nykyisellä päivämäärällä.
void Company::close_project(Params params)
{
    std::string projectName = params.at(0);
    if(projects_.find(projectName) != projects_.end())
    {
        projects_.at(projectName)->endProject(Utils::today);
        std::cout << PROJECT_CLOSED << std::endl;
    }
    else
    {
        std::cout << CANT_FIND << projectName << std::endl;
    }
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja tulostaa yrityksen kaikki projektit sekä näyttää
// niiden alkamis- ja päättymisajankohdat.
void Company::print_projects(Params)
{
    if(projects_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }

    // Projektit luetaan projectOrder-vektorista, johon ne on tallennettu
    // siinä järjestyksessä kun ne on aloitettu, jotta tulostuksesta
    // saadaan oikeanlainen.
    for(unsigned long i = 0; i < projectOrder_.size(); i++)
    {
        std::string projectName = projectOrder_.at(i);
        std::cout << projectName << " : ";
        projects_.at(projectName)->printStart();
        std::cout << " -";

        if(!projects_.at(projectName)->getEnd().is_default())
        {
            std::cout << " ";
            projects_.at(projectName)->printEnd();
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja lisää annetulle projektille vaatimuksen.
// Funktio myös tarkastaa, onko sen nykyisillä työntekijöillä
// pätevyyttä jatkaa projektin parissa. Jos näin ei ole,
// työntekijät poistetaan projektista ja tulostetaan tieto
// heidän poistamisestaan.
void Company::add_requirement(Params params)
{
    std::string projectName = params.at(0);
    std::string requirement = params.at(1);

    if(projects_.find(projectName) != projects_.end())
    {
        if(!projects_.at(projectName)->getEnd().is_default())
        {
            std::cout << CANT_FIND << projectName << std::endl;
        }
        else
        {
            projects_.at(projectName)->addRequirement(requirement);

            std::vector<std::string> workers = projects_.at(projectName)->
                                                    getWorkers();
            std::vector<std::string> nonQualified;
            std::vector<std::string> requirements = projects_.at(projectName)->
                                                    getRequirements();

            // Käydään läpi kaikki projektin työntekijät sekä vaaditut taidot,
            // jotta löydetään kaikki projektiin pätevät henkilöt.
            for(std::string worker : workers)
            {
                // Laskuri, jonka arvo kasvaa, mikäli työntekijällä
                // on yksikin projektissa vaadittava taito, jolloin
                // hän saa jatkaa projektin parissa.
                int qualifiactionCounter = 0;
                for(std::string r : requirements)
                {
                    if(current_staff_.at(worker)->has_skill(r))
                    {
                        qualifiactionCounter++;
                    }
                }
                if(qualifiactionCounter == 0)
                {
                    nonQualified.push_back(worker);
                }
            }

            // Järjestetään tulostettavat akkosjärjestykseen
            // ja tulostetaan halutussa muodossa.
            sort(nonQualified.begin(), nonQualified.end());
            if(nonQualified.size() > 0)
            {
                std::cout << NOT_QUALIFIED << nonQualified.at(0);
                workers.erase(std::remove(workers.begin(),
                                                 workers.end(),
                                                 nonQualified.at(0)));
                if(nonQualified.size() > 1)
                {
                    for(unsigned long i = 1; i < nonQualified.size(); i++)
                    {
                        std::cout <<", " << nonQualified.at(i);
                        workers.erase(std::remove(workers.begin(),
                                                         workers.end(),
                                                         nonQualified.at(i)));
                    }
                }
                std::cout << std::endl;
                projects_.at(projectName)->updateWorkers(workers);
            }
            std::cout << REQUIREMENT_ADDED << projectName << std::endl;
        }
    }
    else
    {
        std::cout << CANT_FIND << projectName << std::endl;
    }
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja lisää annetun työntekijän annetulle projektille.
void Company::assign(Params params)
{
    // Tarkastellaan, että annettu henkilö kuuluu nykyisiin työntekijöihin.
    std::string worker = params.at(0);
    std::string projectName = params.at(1);

    if(current_staff_.find(worker) == current_staff_.end())
    {
        std::cout << CANT_FIND << worker << std::endl;
        return;
    }

    if(projects_.find(projectName) == projects_.end())
    {
        std::cout << CANT_FIND << projectName << std::endl;
        return;
    }

    std::vector<std::string> workers = projects_.at(projectName)->
                                            getWorkers();

    for(std::string w : workers)
    {
        if(w == worker)
        {
            std::cout << CANT_ASSIGN << worker << std::endl;
            return;
        }
    }

    // Tarkastetaan, onko työntekijä jo valmiiksi jollakin projektilla
    // työskentelemässä, jotta listaan ei päädy kaksoiskappaleita.
    bool alreadyWorking = false;
    if(std::find(active_staff_.begin(), active_staff_.end(), worker)
            != active_staff_.end())
    {
        alreadyWorking = true;
    }

    // Mikäli työntekijä ei ole valmiiksi annetussa projektissa,
    // lisätään hänet eri tietovarastoihin, jotta tulostukset
    // saadaan muissa funktioissa oikein.
    if(!projects_.at(projectName)->checkRequirements()
            && current_staff_.find(worker) != current_staff_.end())
    {
        std::cout << STAFF_ASSIGNED << projectName << std::endl;
        current_staff_.at(worker)->addProject(projectName);
        projects_.at(projectName)->addWorkers(worker);
        if(!alreadyWorking)
        {
            active_staff_.push_back(worker);
        }
        return;
    }

    // Mikäli työntekijä ei ole valmiiksi annetussa projektissa,
    // lisätään hänet eri tietovarastoihin, jotta tulostukset
    // saadaan muissa funktioissa oikein.
    if(current_staff_.find(worker) != current_staff_.end())
    {
        std::vector<std::string> requirements = projects_.at(projectName)->
                                                getRequirements();
        for(std::string requirement : requirements)
        {
            if(current_staff_.at(worker)->has_skill(requirement))
            {
                std::cout << STAFF_ASSIGNED << projectName << std::endl;
                projects_.at(projectName)->addWorkers(worker);
                if(!alreadyWorking)
                {
                    active_staff_.push_back(worker);
                }
                return;
            }
        }
    }
    std::cout << CANT_ASSIGN << worker << std::endl;
}

// Funktio ottaa  parametrinaan projektin nimen ja
// tulostaa sen tiedot. Funktio sisältää vain
// tiedon hakua tietosäiliöistä ja tulostuksen muotoilua.
void Company::print_project_info(Params params)
{
    std::string projectName = params.at(0);

    if(projects_.find(projectName) == projects_.end())
    {
        std::cout << CANT_FIND << projectName << std::endl;
        return;
    }

    std::vector<std::string> requirements = projects_.at(projectName)->
                                            getRequirements();
    std::vector<std::string> employees = projects_.at(projectName)->
                                            getWorkers();

    sort(requirements.begin(), requirements.end());
    sort(employees.begin(), employees.end());

    std::cout << projectName << " : ";
    projects_.at(projectName)->printStart();
    std::cout << " -";

    if(!projects_.at(projectName)->getEnd().is_default())
    {
        std::cout << " ";
        projects_.at(projectName)->printEnd();
        std::cout << " ";
    }

    std::cout << std::endl;
    std::cout << "** Requirements: ";

    if(requirements.size() == 0)
    {
        std::cout << "None" << std::endl;
    }
    else
    {

        for(unsigned long i = 0; i < requirements.size(); i++)
        {
            if(i == 0)
            {
                std::cout << requirements.at(i);
            }
            else
            {
                std::cout << ", " << requirements.at(i);
            }
        }
        std::cout << std::endl;
    }

    std::cout << "** Staff: ";
    if(employees.size() == 0)
    {
        std::cout << "None" << std::endl;
    }
    else
    {

        for(unsigned long i = 0; i < employees.size(); i++)
        {
            if(i == 0)
            {
                std::cout << employees.at(i);
            }
            else
            {
                std::cout << "; " << employees.at(i);
            }
        }
        std::cout << std::endl;
    }
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja tulostaa työntekijän tiedot. Funktio sisältää vain
// tiedon hakua tietosäiliöistä ja tulostuksen muotoilua.
void Company::print_employee_info(Params params)
{
    std::string employeeName = params.at(0);

    if(current_staff_.find(employeeName) == current_staff_.end())
    {
        std::cout << CANT_FIND << employeeName << std::endl;
        return;
    }

    std::set<std::string> skills = current_staff_.at(employeeName)->
                                   getSkills();
    std::vector<std::string> projects = current_staff_.at(employeeName)->
                                        getProjects();

    std::cout << "Skills: ";
    if(skills.size() == 0)
    {
        std::cout << "None" << std::endl;
    }
    else
    {
        int i = 0;
        for(auto& skill : skills)
        {
            if(i == 0)
            {
                std::cout << skill;
            }
            else
            {
                std::cout << ", " << skill;
            }
            i++;
        }
        std::cout << std::endl;
    }

    std::cout << "Projects:";
    if(projects.size() == 0)
    {
        std::cout << " None" << std::endl;
    }
    else
    {
        std::cout << std::endl;
        for(std::string project : projects)
        {
            std::cout << "** " << project << " : ";
            projects_.at(project)->printStart();
            std::cout << " -";

            if(!projects_.at(project)->getEnd().is_default())
            {
                std::cout << " ";
                projects_.at(project)->printEnd();
                std::cout << " ";
            }
            std::cout << std::endl;
        }

    }
}

// Funktio ottaa käyttäjän syötteen parametrinaan
// ja tulostaa yrityksessä nykyään työskentelevät työntekijät.
// Funktio sisältää vain tiedon hakua tietosäiliöistä ja
// tulostuksen muotoilua.
void Company::print_active_staff(Params)
{
    if(active_staff_.size() == 0)
    {
        std::cout << "None" << std::endl;
        return;
    }

    sort(active_staff_.begin(), active_staff_.end());
    for(std::string employee : active_staff_)
    {
        std::cout << employee << std::endl;
    }
}
