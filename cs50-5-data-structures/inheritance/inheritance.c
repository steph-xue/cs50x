// The 'inheritance' program simulates genetic inheritance of blood type (based on how many generations are specified)
// The program prints out a possible blood type for a child, their parents, and each subsequent older generation in the family tree
// The oldest parent generation has randomly allocated blood type alleles, one allele from each parent of which is passed down to the child
    // Practicing building a tree structure

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents (parent pointers) and two alleles ('A', 'B', or '0')
typedef struct person
{
    char alleles[2];
    struct person *parents[2];
}
person;

// Generations in the family tree
const int GENERATIONS = 3;

// Length of an indent
const int INDENT_LENGTH = 4;

// Function prototypes
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    // time(0) seeds the time from Unix epoch (seconds since 1970 which is everchanging)
    // Then rand() can be called later to generate a random number everytime using this seed
    srand(time(0));

    // Create a new family tree with number of generations specified
    // Each node represents a person in the family tree with 2 alleles and pointers to parents (if they have any)
    // Returns a pointer 'p' to the head of the family tree (youngest generation)
    person *p = create_family(GENERATIONS);

    // Print each family member in the family tree and their blood types alleles
    print_family(p, 0);

    // Free memory (family tree)
    free_family(p);
}

// Create a new family tree with number of generations specified
// Each node represents a person in the family tree with 2 alleles and pointers to parents (if they have any)
// Returns a pointer as 'p' to the head of the family tree (youngest generation)
// Here generations starts at the max specified, and decreases as we make levels of the family tree
person *create_family(int generations)
{
    // Allocate memory for new person (new node)
    // Return an error message if not enough memory to allocate, NULL results in nothing being created
    person *n = malloc(sizeof(person));
    if (n == NULL)
    {
        printf("Not enough memory to allocate new person\n");
        return NULL;
    }

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parent pointers for current person by recursively calling create_family (and reduce generation by 1)
        // Set parent pointers for current person
        n->parents[0] = create_family(generations - 1);
        n->parents[1] = create_family(generations - 1);

        // Randomly assign current person's alleles based on the alleles of their parents
        n->alleles[0] = n->parents[0]->alleles[rand()%2];
        n->alleles[1] = n->parents[1]->alleles[rand()%2];
    }

    // If there are no generations left to create
    else
    {
        // Set parent pointers to NULL
        n->parents[0] = NULL;
        n->parents[1] = NULL;

        // Randomly assigns and chooses a blood type allele 'A', 'B', or '0' (using random_allele function)
        n->alleles[0] = random_allele();
        n->alleles[1] = random_allele();
    }

    // Return pointer to newly created person
    return n;
}


// Print each family member in the family tree and their blood types alleles
// Generation here starts at 0 (prints child first, and then their parents, grandparents, etc. until all generations are printed)
void print_family(person *p, int generation)
{
    // Handle base case (if pointing to NULL, there is no generations left to print)
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person of the current generation
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print both parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}


// Randomly assigns and chooses a blood type allele 'A', 'B', or '0'
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}


// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // Handle base case: stops freeing nodes once there are none left
    if (p == NULL)
    {
        return;
    }

    // Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free child
    free(p);
}
