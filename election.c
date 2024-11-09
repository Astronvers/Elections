#include <stdio.h>
#include <stdlib.h>

#define NUM_CANDIDATES 4
#define NUM_PRECINCTS 5

void readVotes(FILE *file, int votes[NUM_PRECINCTS][NUM_CANDIDATES]);
void displayTable(int votes[NUM_PRECINCTS][NUM_CANDIDATES]);
void analyzeResults(int votes[NUM_PRECINCTS][NUM_CANDIDATES]);

int main() {
    int votes[NUM_PRECINCTS][NUM_CANDIDATES];
    FILE *file;
    
    // Open the data file
    file = fopen("votes.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    // Read votes from file
    readVotes(file, votes);
    fclose(file);
    
    // Display the table
    displayTable(votes);
    
    // Analyze and display results
    analyzeResults(votes);
    
    return 0;
}

void readVotes(FILE *file, int votes[NUM_PRECINCTS][NUM_CANDIDATES]) {
    for (int i = 0; i < NUM_PRECINCTS; i++) {
        for (int j = 0; j < NUM_CANDIDATES; j++) {
            fscanf(file, "%d", &votes[i][j]);
        }
    }
}

void displayTable(int votes[NUM_PRECINCTS][NUM_CANDIDATES]) {
    printf("\nElection Results:\n");
    printf("\nPrecinct    A    B    C    D\n");
    printf("--------------------------------\n");
    
    for (int i = 0; i < NUM_PRECINCTS; i++) {
        printf("%-9d ", i + 1);
        for (int j = 0; j < NUM_CANDIDATES; j++) {
            printf("%4d ", votes[i][j]);
        }
        printf("\n");
    }
    printf("--------------------------------\n");
}

void analyzeResults(int votes[NUM_PRECINCTS][NUM_CANDIDATES]) {
    int totalVotes = 0;
    int candidateTotals[NUM_CANDIDATES] = {0};
    
    // Calculate totals
    for (int i = 0; i < NUM_PRECINCTS; i++) {
        for (int j = 0; j < NUM_CANDIDATES; j++) {
            candidateTotals[j] += votes[i][j];
            totalVotes += votes[i][j];
        }
    }
    
    // Display totals and percentages
    printf("\nResults Summary:\n");
    printf("---------------\n");
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        float percentage = (float)candidateTotals[i] / totalVotes * 100;
        printf("Candidate %c: %d votes (%.1f%%)\n", 
               'A' + i, candidateTotals[i], percentage);
    }
    printf("Total votes cast: %d\n\n", totalVotes);
    
    // Find winner or top two candidates
    int winner = 0;
    float winnerPercent = (float)candidateTotals[0] / totalVotes * 100;
    
    for (int i = 1; i < NUM_CANDIDATES; i++) {
        float percent = (float)candidateTotals[i] / totalVotes * 100;
        if (candidateTotals[i] > candidateTotals[winner]) {
            winner = i;
            winnerPercent = percent;
        }
    }
    
    if (winnerPercent > 50.0) {
        printf("Candidate %c wins with %.1f%% of the votes!\n", 
               'A' + winner, winnerPercent);
    } else {
        // Find second place
        int secondPlace = (winner == 0) ? 1 : 0;
        for (int i = 0; i < NUM_CANDIDATES; i++) {
            if (i != winner && candidateTotals[i] > candidateTotals[secondPlace]) {
                secondPlace = i;
            }
        }
        printf("Runoff required between Candidate %c and Candidate %c\n",
               'A' + winner, 'A' + secondPlace);
    }
}
