//
// Created by eabag on 24/03/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "shuffle.h"
#include <string.h>
#include <time.h>

void shuffle(int artistIndex, char Artists[][50], int count, const struct ArtistsAndSongs record[]){
    srand(time(NULL));
    int total = 0;
    int seconds;
    int minutes;
    int i;
    int j;
    int t = 0;

    int artistcount[artistIndex];
    int artistarray[count];
    char tripleplay[70][50];

    printf("The Random playlist is:\n");

    //initialising all values in array to 0
    //setup for making sure a song doesnt appear twice in a playlist or three in a row
    for (i = 0; i < count; i++) {
        artistarray[i] = 0;
    }

    //initialising all values in array to 0
    //setup for making sure artist has max of 3 songs in playlist
    for (i = 0; i <= artistIndex; i++) {
        artistcount[i] = 0;
    }

    //• An artiste cannot have more than two songs in a row



//3600 is 1 hour in seconds
//The last song is played at 3599 = 59:59
    while (total < 3600) {

        //random selected song from playlist
        j = rand() % count;

        //checking through the whole array if they have 3 or more songs
        for (i = 0; i <= artistIndex; i++){

            //a check to see if the artist of the chosen song has less than
            //3 songs in the playlist, if they do continue, if not then try again
            if ((strcmp(Artists[i], record[j].Artist_name) == 0) && (artistcount[i] < 3)) {

                //if it is going to be three artist's songs it a row dont allow it
                if(!((strcmp(tripleplay[t],record[j].Artist_name) == 0) && (strcmp(tripleplay[t - 1],record[j].Artist_name) == 0))){

                    //if the artists song hasn't been used yet
                    if (artistarray[j] == 0) {

                        //converting char to int and summing minutes and seconds together
                        //to count for an hour
                        minutes = (atoi(record[j].time_minutes));
                        int minutes1 = minutes * 60;
                        seconds = (atoi(record[j].time_seconds));
                        total = (total + (seconds + minutes1));

                        //print the song in correct format
                        printf("%s: \"%s\" (%s:%s)\n", record[j].Artist_name, record[j].song, record[j].time_minutes,record[j].time_seconds);

                        //the artists song can no longer come up now
                        artistarray[j] = 1;

                        //loop to stop artists having more than 3 songs
                        for (i = 0; i <= artistIndex; i++) {

                            //if they are the same increment the i in the artistcount array
                            //when this reaches 3 the artist cant have a song in the playlist again
                            if (strcmp(Artists[i], record[j].Artist_name) == 0) {
                                artistcount[i]++;
                            }

                        }

                        //to stop artist from having three songs in a row
                        //copy songs into this and check i-1 and i
                        strcpy(tripleplay[t], record[j].Artist_name);
                        t++;

                    }
                }

            }

        }
    }
    printf("Total duration: %d minutes %d seconds", total/60, total%60);

}
