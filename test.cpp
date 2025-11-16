#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string toLowerCase(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// STRUCTURE OF CANDIDATE WITH FIELDS

class Candidate {
public:
    string name;
    int age;
    vector<string> skills;
    string domain;
    string jobTitle;
    int experience;
    string location;
    int salary;
    int leadershipExp;
    int internationalExp;
    string degree;
    int noticePeriod;

    Candidate(string name,
              int age,
              vector<string> skills,
              string domain,
              string jobTitle,
              int experience,
              string location,
              int salary,
              int leadershipExp,
              int internationalExp,
              string degree,
              int noticePeriod)
    {
        this->name = name;
        this->age = age;
        this->skills = skills;
        this->domain = domain;
        this->jobTitle = jobTitle;
        this->experience = experience;
        this->location = location;
        this->salary = salary;
        this->leadershipExp = leadershipExp;
        this->internationalExp = internationalExp;
        this->degree = degree;
        this->noticePeriod = noticePeriod;
    }
};

// Helper to convert empty input to 0
int safeIntInput() {
    string s;
    getline(cin, s);
    if (s.empty()) return 0;
    return stoi(s);
}

// Helper to convert comma-separated skills
vector<string> parseSkills(const string& s) {
    vector<string> result;
    string temp = "";
    for (char c : s) {
        if (c == ',') {
            if (!temp.empty()) result.push_back(toLowerCase(temp));
            temp = "";
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) result.push_back(toLowerCase(temp));
    return result;
}

// Print candidate
void printCandidate(const Candidate& c) {
    cout << "\n----- BEST MATCHING CANDIDATE -----\n";
    cout << "Name: " << c.name << endl;
    cout << "Age: " << c.age << endl;

    cout << "Skills: ";
    for (string s : c.skills) cout << s << " ";
    cout << endl;

    cout << "Domain: " << c.domain << endl;
    cout << "Job Title: " << c.jobTitle << endl;
    cout << "Experience: " << c.experience << " years\n";
    cout << "Location: " << c.location << endl;
    cout << "Salary: " << c.salary << endl;
    cout << "Leadership Experience: " << c.leadershipExp << " years\n";
    cout << "International Experience: " << c.internationalExp << " years\n";
    cout << "Degree: " << c.degree << endl;
    cout << "Notice Period: " << c.noticePeriod << endl;
}

int main() {

    //------------------ PREDEFINED CANDIDATES ------------------
    vector<Candidate> candidates = {

        Candidate("Sneha Iyer", 38,
                  {"project management", "agile", "communication"},
                  "management", "project manager",
                  12, "mumbai", 2200000, 6, 2, "mba", 60),

        Candidate("Rahul Mehta", 26,
                  {"javascript", "react", "node"},
                  "web development", "frontend developer",
                  3, "pune", 950000, 1, 0, "b.e", 30),

        Candidate("Ananya Gupta", 25,
                  {"html", "css", "javascript", "react"},
                  "web development", "frontend developer",
                  5, "delhi", 850000, 1, 0, "b.tech", 45),

        Candidate("Amit Sharma", 29,
                  {"c++", "python", "sql"},
                  "software engineering", "software developer",
                  5, "bangalore", 1200000, 2, 0, "b.tech", 60),

        Candidate("Karan Patel", 31,
                  {"java", "spring boot", "microservices"},
                  "software engineering", "backend developer",
                  7, "hyderabad", 1600000, 3, 1, "m.tech", 90),

        Candidate("Arjun Reddy", 27,
                  {"python", "machine learning", "tensorflow"},
                  "data science", "data scientist",
                  4, "chennai", 1100000, 1, 1, "m.sc", 30),

        Candidate("Meera Nair", 30,
                  {"python", "deep learning", "nlp"},
                  "data science", "senior data scientist",
                  6, "bangalore", 1700000, 2, 1, "m.tech ai", 45)
    };

    //------------------ USER INPUT (JOB REQUIREMENT) ------------------

    string skillsInput, domain, jobTitle, location, degree;
    int experience, salary, leadershipExp, internationalExp, noticePeriod;

    cout << "Enter required skills (comma separated): ";
    getline(cin, skillsInput);
    vector<string> skills;
    if (!skillsInput.empty()) skills = parseSkills(skillsInput);

    cout << "Enter Domain: ";
    getline(cin, domain);
    domain = toLowerCase(domain);

    cout << "Enter Job Title: ";
    getline(cin, jobTitle);
    jobTitle = toLowerCase(jobTitle);

    cout << "Enter Experience (years): ";
    experience = safeIntInput();

    cout << "Enter Location: ";
    getline(cin, location);
    location = toLowerCase(location);

    cout << "Enter Max Salary: ";
    salary = safeIntInput();

    cout << "Enter Leadership Experience (years): ";
    leadershipExp = safeIntInput();

    cout << "Enter International Experience (years): ";
    internationalExp = safeIntInput();

    cout << "Enter Degree: ";
    getline(cin, degree);
    degree = toLowerCase(degree);

    cout << "Enter Notice Period: ";
    noticePeriod = safeIntInput();

    Candidate inputCandidate(
        "", 0, skills, domain, jobTitle, experience,
        location, salary, leadershipExp, internationalExp,
        degree, noticePeriod
    );

    //------------------ SCORING ------------------

    double maxScore = 0;
    Candidate bestCandidate("", 0, {}, "", "", 0, "", 0, 0, 0, "", 0);

    for (int i = 0; i < candidates.size(); i++) {

        Candidate temp = candidates[i];
        double score = 0;

      
        string candLocation = toLowerCase(temp.location);
        string candDegree = toLowerCase(temp.degree);
        string candDomain = toLowerCase(temp.domain);
        string candJob = toLowerCase(temp.jobTitle);

        // comparing location,degree,domaina nd jobTitle  ---- Directly either yes or no 

        if (toLowerCase(inputCandidate.location) == candLocation) score += 0.05;
        if (toLowerCase(inputCandidate.degree) == candDegree) score += 0.02;
        if (toLowerCase(inputCandidate.domain) == candDomain) score += 0.15;
        if (toLowerCase(inputCandidate.jobTitle) == candJob) score += 0.15;
       
        // comparing experience
        
        int currentExp = temp.experience;
        int expectedExp = inputCandidate.experience;
        if (expectedExp > 0)
            score += 0.10 * ((double)min(currentExp, expectedExp) / expectedExp);

          // comparing Leadershipexperience  

        int currentLead = temp.leadershipExp;
        int expectedLead = inputCandidate.leadershipExp;
        if (expectedLead > 0)
            score += 0.05 * ((double)min(currentLead, expectedLead) / expectedLead);

        // comparing International experience
        int currentIntl = temp.internationalExp;
        int expectedIntl = inputCandidate.internationalExp;
        if (expectedIntl > 0)
            score += 0.03 * ((double)min(currentIntl, expectedIntl) / expectedIntl);

        // comparing notice period

        int currentNotice = temp.noticePeriod;
        int expectedNotice = inputCandidate.noticePeriod;
        if (expectedNotice > 0 && currentNotice > 0) {
            if (currentNotice <= expectedNotice)
                score += 0.05;
            else
                score += 0.05 * ((double)expectedNotice / currentNotice);
        }

         // comparing salaries

        double currentSalary = temp.salary;
        double offeredSalary = inputCandidate.salary;

        if (offeredSalary > 0) {
            if (currentSalary <= offeredSalary)
                score += 0.10;
            else if (currentSalary > 1.5 * offeredSalary - 1)
                score += 0.10 * 0.5;
            else
                score += 0.10 * 0.2;
        }

        //comparing skills

        vector<string> expectedSkills = inputCandidate.skills;
        vector<string> currentSkills = temp.skills;

        int total = expectedSkills.size();
        int count = 0;

        if (total > 0) {
            for (string cs : currentSkills)
                for (string es : expectedSkills)
                    if (toLowerCase(cs) == toLowerCase(es)) count++;

            score += 0.30 * ((double)count / total);
        }

        if (score > maxScore) {
            maxScore = score;
            bestCandidate = temp;
        }
    }

    //---------PRINTING BEST CANDIDATE WITH BEST SCORE-----------

    printCandidate(bestCandidate);

    return 0;
}
