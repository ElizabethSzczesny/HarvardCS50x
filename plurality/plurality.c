#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
int MAX = 9;

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[9];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void swap(candidate *a, candidate *b);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++){
    if( strcasecmp(name, candidates[i].name) == 0){
        candidates[i].votes++;
        return true;
    }
}
return false;
}

void swap(candidate *a, candidate *b)
{
candidate tmp = *a;
*a = *b;
*b = tmp;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++){
        //candidate spotmin = candidates[i];
        int spotmin = i;
            for (int j = i + 1; j < candidate_count; j++){
            if (candidates[j].votes < candidates[i].votes){
             //selection sort over the vote numbers
            //swap
            //candidates[i] = candidates[j - 1];
            //candidates[j - 1] = spotmin;
            //spotmin = candidates[i];
            spotmin = j;
            swap(&candidates[spotmin], &candidates[i]);
            }
        }
    }

    //printf("%s + %i, %s + %i\n", candidates[0].name, candidates[0].votes, candidates[1].name, candidates[1].votes);

    for (int i = 0; i < candidate_count - 1; i++){
    if (candidates[candidate_count - 1].votes == candidates[i].votes){
        printf("%s\n", candidates[i].name);
    }
    }
    printf("%s\n", candidates[candidate_count - 1].name); //received the most votes if furthest right in sorted line
    return;
}