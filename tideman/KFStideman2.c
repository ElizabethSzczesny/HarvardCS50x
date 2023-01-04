#include <cs50.h>
#include <stdio.h>
#include <strings.h>

//  Declaration of GLOBAL VARIABLES
// Max number of candidates
int MAX = 9;
// will input actual number of candidates
int candidate_count;
// Array of candidates (where the names of the candidates are populated)
string candidates[9];

// preferences[a][b] is number of voters who prefer candidate a over candidate b   (2D preferences array)
int preferences[9][9];

// Each pair has a winner and a loser
// each pair includes the winner’s candidate index and the loser’s candidate index
typedef struct
{
    int winner;
    int loser;
}
pair;
// Array of pairs (each pair has a winner and a loser)
// this array of pairs will represent all of the pairs of candidates
// (for which  the winner candidate is preferred over the loser candidate) on a ballot in the election.
pair pairs[9 * (9 - 1) / 2];
// will count the pairs as they are populated
int pair_count;

// locked[a][b] means candidate a is locked in over candidate b
// (2D locked matrix) which represents the candidate graph
bool locked[9][9];
// locked[a][b] being true represents the existence of an edge pointing from candidate a to candidate b
// and false means that there is no edge from candidate a to candidate b.

// Function Prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //  already called voter (only) in main

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (ranks[i] == j)
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if (k > i)
                    {
                        for (int l = 0; l < candidate_count; l++)
                        {
                            if (ranks[k] == l)
                            {
                                preferences[j][l] += 1;
                            }
                        }
                    }
                }
            }
        }
        printf("\n");
        printf("%i,%i,%i,%i,%i,%i,%i,%i,%i\n", preferences[0][0], preferences[0][1], preferences[0][2],
            preferences[0][3], preferences[0][4], preferences[0][5], preferences[0][6],
            preferences[0][7], preferences[0][8]);
        printf("%i,%i,%i,%i,%i,%i,%i,%i,%i\n", preferences[1][0], preferences[1][1], preferences[1][2],
            preferences[1][3], preferences[1][4], preferences[1][5], preferences[1][6],
            preferences[1][7], preferences[1][8]);
        printf("%i,%i,%i,%i,%i,%i,%i,%i,%i\n", preferences[2][0], preferences[2][1], preferences[2][2],
            preferences[2][3], preferences[2][4], preferences[2][5], preferences[2][6],
            preferences[2][7], preferences[2][8]);
        printf("%i,%i,%i,%i,%i,%i,%i,%i,%i\n", preferences[3][0], preferences[3][1], preferences[3][2],
            preferences[3][3], preferences[3][4], preferences[3][5], preferences[3][6],
            preferences[3][7], preferences[3][8]);
        printf("%i,%i,%i,%i,%i,%i,%i,%i,%i\n", preferences[4][0], preferences[4][1], preferences[4][2],
            preferences[4][3], preferences[4][4], preferences[4][5], preferences[4][6],
            preferences[4][7], preferences[4][8]);
        printf("%i,%i,%i,%i,%i,%i,%i,%i,%i\n", preferences[5][0], preferences[5][1], preferences[5][2],
            preferences[5][3], preferences[5][4], preferences[5][5], preferences[5][6],
            preferences[5][7], preferences[5][8]);
        printf("%i,%i,%i,%i,%i,%i,%i,%i,%i\n", preferences[6][0], preferences[6][1], preferences[6][2],
            preferences[6][3], preferences[6][4], preferences[6][5], preferences[6][6],
            preferences[6][7], preferences[6][8]);
        printf("%i,%i,%i,%i,%i,%i,%i,%i,%i\n", preferences[7][0], preferences[7][1], preferences[7][2],
            preferences[7][3], preferences[7][4], preferences[7][5], preferences[7][6],
            preferences[7][7], preferences[7][8]);
        printf("%i,%i,%i,%i,%i,%i,%i,%i,%i\n", preferences[8][0], preferences[8][1], preferences[8][2],
            preferences[8][3], preferences[8][4], preferences[8][5], preferences[8][6],
            preferences[8][7], preferences[8][8]);
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //  out of the main loop above, create pairs of winner first, then loser

    int total_pairs = candidate_count * (candidate_count - 1) / 2;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                //declare that you are making a pair and name it
                //pair _i = int winner index, int loser index
                pair _names = { i, j };
                pairs[pair_count] = _names;
                //update pair_count
                pair_count++;
            }
        }
    }

    printf("pair_count: %i total_pairs: %i candidate_count: %i\n", pair_count, total_pairs, candidate_count);

    for (int k = 0; k < pair_count; k++)
    {
        printf("Pair %i - Winner: %i  - Loser: %i --since-- Winner Votes: %i  - Loser Votes: %i\n",
            k, pairs[k].winner, pairs[k].loser,
            preferences[pairs[k].winner][pairs[k].loser],
            preferences[pairs[k].loser][pairs[k].winner]);
    }
    return;
}

// helper function for sorting the pairs
void swap(pair *a, pair *b)
{
    pair tmp = *a;
    *a = *b;
    *b = tmp;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //  run through all the pairs
    for (int i = 0; i < pair_count; i++)
    {
        int spotmax = i;
        for (int j = i + 1; j < pair_count; j++) {
            //pairs[i].winner their preferences over pairs[i].loser
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                spotmax = j;
                swap(&pairs[spotmax], &pairs[i]);
            }
        }
    }

    for (int k = 0; k < pair_count; k++)
    {
        printf("Pair %i - Winner: %i  - Loser: %i\n", k, pairs[k].winner, pairs[k].loser);
    }
    return;
}
void recursive(int starting_point, int first_winner, int first_loser)
{
    int visited[9] = { 0,0,0,0,0,0,0,0,0 };

    for (int m = 0; m < candidate_count; m++)
    {
        if (locked[starting_point][m] == true && visited[m] == 0)
        {
            visited[m] = 1;
            if (locked[m][first_winner] == true)
            {
                locked[first_winner][first_loser] = false;
                printf("locked[%i][%i] = false\n", first_winner, first_loser);
                return;
            }
            int next_starting_point = m;
            printf("next_starting_point: %i \n", next_starting_point);
            recursive(next_starting_point, first_winner, first_loser);
            if (locked[first_winner][first_loser] == false) { return; }
        }
    }
    locked[first_winner][first_loser] = true;
    printf("locked[%i][%i] = true\n", first_winner, first_loser);
    return;
}
void lock_pairs(void)
{
    //  locked 2-D array of boolean values
    //  for each pair find the winner and loser
    int n = 0;

    while (n < pair_count)
    {
        int first_winner = pairs[n].winner;
        int first_loser = pairs[n].loser;
        int starting_point = pairs[n].loser;
        printf("%i,%i  starting_point: %i \n", pairs[n].winner, pairs[n].loser, starting_point);
        recursive(starting_point, first_winner, first_loser);
        n++;
    }

    printf("%s,%s,%s,%s,%s,%s,%s,%s,%s\n", locked[0][0] ? "true" : "false", locked[0][1] ? "true" : "false",
        locked[0][2] ? "true" : "false", locked[0][3] ? "true" : "false", locked[0][4] ? "true" : "false",
        locked[0][5] ? "true" : "false", locked[0][6] ? "true" : "false", locked[0][7] ? "true" : "false",
        locked[0][8] ? "true" : "false");
    printf("%s,%s,%s,%s,%s,%s,%s,%s,%s\n", locked[1][0] ? "true" : "false", locked[1][1] ? "true" : "false",
        locked[1][2] ? "true" : "false", locked[1][3] ? "true" : "false", locked[1][4] ? "true" : "false",
        locked[1][5] ? "true" : "false", locked[1][6] ? "true" : "false", locked[1][7] ? "true" : "false",
        locked[1][8] ? "true" : "false");
    printf("%s,%s,%s,%s,%s,%s,%s,%s,%s\n", locked[2][0] ? "true" : "false", locked[2][1] ? "true" : "false",
        locked[2][2] ? "true" : "false", locked[2][3] ? "true" : "false", locked[2][4] ? "true" : "false",
        locked[2][5] ? "true" : "false", locked[2][6] ? "true" : "false", locked[2][7] ? "true" : "false",
        locked[2][8] ? "true" : "false");
    printf("%s,%s,%s,%s,%s,%s,%s,%s,%s\n", locked[3][0] ? "true" : "false", locked[3][1] ? "true" : "false",
        locked[3][2] ? "true" : "false", locked[3][3] ? "true" : "false", locked[3][4] ? "true" : "false",
        locked[3][5] ? "true" : "false", locked[3][6] ? "true" : "false", locked[3][7] ? "true" : "false",
        locked[3][8] ? "true" : "false");
    printf("%s,%s,%s,%s,%s,%s,%s,%s,%s\n", locked[4][0] ? "true" : "false", locked[4][1] ? "true" : "false",
        locked[4][2] ? "true" : "false", locked[4][3] ? "true" : "false", locked[4][4] ? "true" : "false",
        locked[4][5] ? "true" : "false", locked[4][6] ? "true" : "false", locked[4][7] ? "true" : "false",
        locked[4][8] ? "true" : "false");
    printf("%s,%s,%s,%s,%s,%s,%s,%s,%s\n", locked[5][0] ? "true" : "false", locked[5][1] ? "true" : "false",
        locked[5][2] ? "true" : "false", locked[5][3] ? "true" : "false", locked[5][4] ? "true" : "false",
        locked[5][5] ? "true" : "false", locked[5][6] ? "true" : "false", locked[5][7] ? "true" : "false",
        locked[5][8] ? "true" : "false");
    printf("%s,%s,%s,%s,%s,%s,%s,%s,%s\n", locked[6][0] ? "true" : "false", locked[6][1] ? "true" : "false",
        locked[6][2] ? "true" : "false", locked[6][3] ? "true" : "false", locked[6][4] ? "true" : "false",
        locked[6][5] ? "true" : "false", locked[6][6] ? "true" : "false", locked[6][7] ? "true" : "false",
        locked[6][8] ? "true" : "false");
    printf("%s,%s,%s,%s,%s,%s,%s,%s,%s\n", locked[7][0] ? "true" : "false", locked[7][1] ? "true" : "false",
        locked[7][2] ? "true" : "false", locked[7][3] ? "true" : "false", locked[7][4] ? "true" : "false",
        locked[7][5] ? "true" : "false", locked[7][6] ? "true" : "false", locked[7][7] ? "true" : "false",
        locked[7][8] ? "true" : "false");
    printf("%s,%s,%s,%s,%s,%s,%s,%s,%s\n", locked[8][0] ? "true" : "false", locked[8][1] ? "true" : "false",
        locked[8][2] ? "true" : "false", locked[8][3] ? "true" : "false", locked[8][4] ? "true" : "false",
        locked[8][5] ? "true" : "false", locked[8][6] ? "true" : "false", locked[8][7] ? "true" : "false",
        locked[8][8] ? "true" : "false");
    return;
}

// Print the winner of the election
void print_winner(void)
{
    string winner = "";
    for (int m = 0; m < candidate_count; m++)
    {
        for (int n = 0; n < candidate_count; n++)
        {
            if (locked[m][n] == false && n != m)
            {
                break;
            }
            else if (locked[m][n] == false && n == m)
            {
                continue;
            }
            else if (locked[m][n] == true && n != candidate_count - 1 && m != candidate_count - 1)
            {
                continue;
            }
            else
            {
                winner = candidates[m];
                //  tell everyone who the winner is …
                printf("%s\n", winner);
                return;
            }
        }
    }
}
