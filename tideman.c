#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
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
        if (strcmp(name, candidates[i]) == 0)
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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int y = i + 1; y < candidate_count; y++)
        {
            preferences[ranks[i]][ranks[y]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int y = 0; y < candidate_count; y++)
        {
            if (i == y)
            {
                continue;
            }
            if (preferences[i][y] > preferences[y][i])
            {
                pair temp;
                temp.winner = i;
                temp.loser = y;
                pairs[pair_count] = temp;
                pair_count++;
            }
        }
    }
    return;
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0 ; i < pair_count; i++)
    {
        for (int y = 0; y < pair_count - 1; y++)
        {
            int first_num = preferences[pairs[y].winner][pairs[y].loser] - preferences[pairs[y].loser][pairs[y].winner];
            int second_num = preferences[pairs[y + 1].winner][pairs[y + 1].loser] - preferences[pairs[y + 1].loser][pairs[y + 1].winner];
            if (first_num < second_num)
            {
                pair temp = pairs[y];
                pairs[y] = pairs[y + 1];
                pairs[y + 1] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        bool ar = false;
        int pos;
        for (int y = 0; y < candidate_count; y++)
        {
            if (locked[y][pairs[i].winner] == true)
            {
                ar = true;
                pos = y;
                break;
            }
        }
        if (ar)
        {
            if (locked[pairs[i].loser][pos] == false)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
            else
            {
                continue;
            }
        }
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    int c = candidate_count;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int y = 0; y < candidate_count; y++)
        {
            if (locked[y][i] == true)
            {
                c--;
                break;
            }
        }
    }
    if (c == 0)
    {
        locked[pairs[candidate_count - 1].winner][pairs[candidate_count - 1].loser] = false;
    }
    return;
}
// Print the winner of the election
void print_winner(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        bool found = false;
        for (int y = 0; y < candidate_count; y++)
        {
            if (locked[y][i] == true)
            {
                found = true;
            }
        }
        if (!found)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}

