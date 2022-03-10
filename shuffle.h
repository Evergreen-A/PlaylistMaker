//
// Created by eabag on 24/03/2021.
//

#ifndef SOFTWAREPROJECT1_SHUFFLE_H
#define SOFTWAREPROJECT1_SHUFFLE_H

//initialising global struct for All artists and their songs
struct ArtistsAndSongs{
    char Artist_name[30];
    char song[50];
    char time_minutes[50];
    char time_seconds[50];
};

#endif //SOFTWAREPROJECT1_SHUFFLE_H

//function to shuffle and print the array
void shuffle(int artistIndex, char Artists[][50], int count, const struct ArtistsAndSongs record[]);

