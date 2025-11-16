A C++-based intelligent matching engine that selects the best-suited candidate from a predefined database based on a job requirement entered by the user.

This project demonstrates a weighted scoring algorithm that evaluates candidates on multiple parameters such as skills, experience, job title, domain, salary, degree, notice period, leadership exposure, and international experience.

🚀 Features

Predefined list of candidates across:

Management

Web Development

Software Engineering

Data Science

User enters job requirements (skills, domain, experience, etc.)

System calculates a match score for every candidate

Uses weighted multi-factor scoring

Selects and prints the best matching candidate

Case-insensitive comparison for all string fields

Supports empty inputs (treated as optional criteria)

# Core Logic — How Matching Works
1️. User Inputs Job Requirements

The user enters:

Required Skills (comma-separated)

Domain

Job Title

Experience

Location

Maximum Salary

Leadership Experience

International Experience

Degree

Notice Period

Empty fields are allowed — empty/0 means “this criterion is optional”.

2️. Weighted Scoring System

Each candidate is evaluated against the input using predefined weights:

Attribute	Weight,
Skills	0.30,
Domain match	0.15,
Job Title match	0.15,
Experience match	0.10,
Salary expectation	0.10,
Location match	0.05,
Notice Period	0.05,
Leadership Exp	0.05,
International Exp	0.03,
Degree match	0.02

These weights reflect the importance of each category in real-world hiring priorities.

# Algorithm Steps (High-Level Overview)
Step 1 — Convert all strings to lowercase

Ensures fair comparison:

React == react == REACT

Step 2 — Parse user skills into a vector
Step 3 — Loop through all predefined candidates

For each candidate:

score = 0

Step 4 — Add score based on direct matches

Location, degree, domain, job title → fixed weight addition if matched.

Step 5 — Experience calculation

If user provides expected experience:

expScore = (min(candidateExp, expectedExp) / expectedExp)
score += expScore * 0.10

Step 6 — Leadership & International Experience

Same logic as above but using their respective weights.

Step 7 — Salary

If candidate salary <= offered salary → full points
Else → partial score based on how far it deviates.

Step 8 — Notice Period

If candidate noticePeriod <= expectedNotice → full 0.05
Else → proportional reduction.

Step 9 — Skills Matching

Count how many required skills exist in candidate's skills:

skillScore = matchedSkills / totalRequiredSkills
score += skillScore * 0.30

Step 10 — Track highest-scoring candidate

If score > maxScore → update bestCandidate.

Step 11 — Print final best candidate