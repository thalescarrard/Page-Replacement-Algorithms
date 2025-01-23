// Anthony Carvalho - 6365160
// Thales Moraes - 6332398

// This project implements two-page replacement algorithms:
//  FIFO (First-In, First-Out) and LRU (Least Recently Used), 
//  simulating how operating systems manage memory pages. 
//  The program calculates page faults and outputs the final 
//  state of memory for each replacement policy.

#include <stdio.h>
#include <stdlib.h>

// Function to implement FIFO page replacement
void fifo(int *pages, int num_pages, int num_frames) {
    int *frame = calloc(num_frames, sizeof(int));
    int faults = 0, next_to_replace = 0;

    // Initialize frames as empty
    for (int i = 0; i < num_frames; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < num_frames; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }

        // If page not found, replace using FIFO
        if (!found) {
            frame[next_to_replace] = page;
            next_to_replace = (next_to_replace + 1) % num_frames;
            faults++;
        }
    }

    // Output results
    printf("FIFO: %d page faults\n", faults);
    printf("Final state of memory: ");
    for (int i = 0; i < num_frames; i++) {
        printf("%d ", frame[i]);
    }
    printf("\n");
    free(frame);
}

// Function implement LRU page replacement
void lru(int *pages, int num_pages, int num_frames) {
    int *frame = calloc(num_frames, sizeof(int));
    int *last_used = calloc(num_frames, sizeof(int));
    int faults = 0;
    // initialize frames as empty
    for (int i = 0; i < num_frames; i++) {
        frame[i] = -1;
        last_used[i] = -1;
    }
    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int found = 0;
        // Check if the page is already in the frame
        for (int j = 0; j < num_frames; j++) {
            if (frame[j] == page) {
                found = 1;
                last_used[j] = i; // update the last used time
                break;
            }
        }
        // if the page not found, replace using LRU
        if (!found) {
            int lru_index = 0;

            // Find the least recently used page
            for (int j = 1; j < num_frames; j++) {
                if (last_used[j] < last_used[lru_index]) {
                    lru_index = j;
                }
            }

            frame[lru_index] = page;
            last_used[lru_index] = i;
            faults++;
        }
    }
    // Output results
    printf("LRU: %d page faults\n", faults);
    printf("Final state of memory: ");
    for (int i = 0; i < num_frames; i++) {
        printf("%d ", frame[i]);
    }
    printf("\n");
    free(frame);
    free(last_used);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./PA5.c numberofframes page1 page2 ... pageN\n");
        return 1;
    }

    int num_frames = atoi(argv[1]);
    if (num_frames < 1 || num_frames > 10) {
        printf("Error: Number of frames must be between 1 and 10.\n");
        return 1;
    }

    int num_pages = argc - 2;
    int *pages = malloc(num_pages * sizeof(int));
    for (int i = 0; i < num_pages; i++) {
        pages[i] = atoi(argv[i + 2]);
    }

    fifo(pages, num_pages, num_frames);
    lru(pages, num_pages, num_frames);

    free(pages);
    return 0;
}
