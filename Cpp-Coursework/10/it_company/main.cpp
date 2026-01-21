/* COMP.CS.110 Project 3: IT-company
 * ===========================
 * Tekijä: Kristian Taipale
 * Opiskelijanumero: 246385
 *
 * Ohjelma ottaa käyttäjältä syötteitä ja tekee niiden
 * pohjalta hakuja ja muokkauksia yrityksen tietoihin.
 * Ohjelman toimintoja ovat set_date, joka asettaa nykyisen päivämäärän,
 * advance_date, joka muuttaa päivämäärää annetun verran, recruit, joka
 * lisää annetun henkilön yrityksen työntekijäksi, leave, joka poistaa
 * henkilön yrityksen työntekijöistä, add_skill, joka lisää annetulle
 * henkilölle tietyn taidon, print_current_stuff, joka tulostaa nykyiset
 * työntekijät, create_project, joka luo yritykselle uuden projektin,
 * close_project, joka sulkee käynnissä olevan projektin ja tallentaa
 * sen sulkemispäivämäärän, print_projects, joka tulostaa tiedon kaikista
 * yrityksen nykyisistä ja päättyneistä projekteista sekä niiden ajankohdista,
 * add_requirement, joka lisää tiettyyn projektiin sen vaatimat taidot,
 * assign, joka lisää henkilön kyseisen projektin työntekijäksi,
 * print_project_info, joka tulostaa projektin tiedot tekijöistä, vaadituista
 * taidoista sekä ajankohdasta, jolloin se on ollut käynnissä,
 * print_employee_info, joka tulostaa työntekijän taidot ja projektit, joissa
 * hän on mukana sekä print_active_staff, joka tulostaa yrityksessä nykyään
 * työskentelevät työntekijät.
 * */

#include "cli.hh"
#include "company.hh"

const std::string PROMPT = "IT> ";

int main()
{
    Company* company = new Company();
    Cli cli(company, PROMPT);
    while( cli.exec() ){}

    delete company;
    return EXIT_SUCCESS;
}
