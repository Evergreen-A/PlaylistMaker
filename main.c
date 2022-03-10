/*
 * 20/03/2021
 *Evergreen Abagha 20432286
 *
 * C programming software engineering project
 * To make a playlist sorter and shuffler that outputs all songs sorted and a shuffled playlist with restrictions
 *
 * I included areas in my code where insertion sort would be positioned and what it would look like but it didnt work for me.
 * My loop to output the shuffled playlist assumes there will be enough songs to make up an hour, if it doesn't my program will break
 *
 * Clion only works for me when i send absolute links to be read in as a file or as an argument to my main,
 * so if just writing the file names i sent dont work write the absolute link, please and thank you.
 *
 */

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shuffle.h"


//rules for user to input the text manually
void rules(void);

//keyboard input from user that also returns row size (i)
int keyboard(char read[][50]);

//taking in command line arguments
int main(int argc, char *argv[]) {



    //initializing section/////////////////////////////////////////////////////////////////////////////////////////////////

    char read[70][50];//2d array that will be used to read in from file and keyboard
    char AllSongs[70][50];//the things in the read 2d array will be copied into here
    char lastartist[1][50];
    char Tokenise[70][50];
    int i = 0;
    int j;
    int holder = 0;
    int artistIndex = 0;//counts how many artists there are
    int comparing;
    char temp[40];
    char Artists[15][50];//array of just artists
    int rowsize;





    //reading in file section///////////////////////////////////////////////////////////////////////////////////////////

    //if the first argument isn't empty use it try to open a file
    if(argv[1] != NULL)
    {
        printf("%s\n", argv[1]);
        FILE *fp = fopen(argv[1], "r");

        //if file is empty print error
        if(fp == NULL)
        {
            printf("Error! The file does not exist, or is not readable!\n");
            printf("Now trying to search for a file called Artistes+songs.txt\n\n");
        }

        while (fgets(read[i], sizeof(read[i]), fp)) {
            //remove newline character
            char len = strlen(read[i]);
            if( read[i][len-1] == '\n' )
                read[i][len-1] = 0;
            i++;
        }

        fclose(fp);
    }



    //if the first argument is empty search for file called artistes+song
    if(argv[1] == NULL)
    {

        //clion only opens absolute links for me so substitute this for the file name called Artistes+songs.txt or SongsandArtists.txt
        //you could also send the link to the file as an argument ans that also works
        FILE *fp1 = fopen("C:\\Users\\eabag\\Desktop\\collegeyear1\\Springsemester\\softwareengineering\\Softwareproject1\\Artistes+songs1.txt", "r");

        //if file is empty
        if(fp1 == NULL)
        {
            printf("Error! File not found\n\n");
            printf("Type out the artist name and songs in the correct format\n");
            rules();
            i = keyboard(read);
            //make function that reads in user input and send to 2d array read[i][j]
        }

        while (fgets(read[i], sizeof(read[i]), fp1)) {
            //remove newline character
            char len = strlen(read[i]);
            if( read[i][len-1] == '\n' )
                read[i][len-1] = 0;
            i++;
        }

        fclose(fp1);
    }



    //number of times incrementing i is the number of rows
    rowsize = i;




    //sorting section/////////////////////////////////////////////////////////////////////////////////////////////////////////


    //i = number of rows then copy the array
    for ( j = 0; j < i; j++) {

        //copying inputted songs into new 2darray
        strcpy(AllSongs[j], read[j]);

        //checking if the line is empty, if it is sort the values before it but not the artist name (only songs)
        if(!(((strcmp(AllSongs[j],"\n")) != 0) && ((strcmp(AllSongs[j],"\r\n")) != 0) && ((strcmp(AllSongs[j],"\0")) != 0) && 1)){

            //putting the artist names into an array to then sort it later
            strcpy(Artists[artistIndex], AllSongs[holder]);

            int holder1 = holder + 1;
            int j1 = j - 1;

            //sorting songs in the alphabetical order
            while (holder1 <= j1){

                for (comparing = holder1 + 1; comparing <= j1; comparing++) {

                    if (strcmp(AllSongs[holder1], AllSongs[comparing]) > 0) {
                        strcpy(temp, AllSongs[holder1]);
                        strcpy(AllSongs[holder1], AllSongs[comparing]);
                        strcpy(AllSongs[comparing], temp);
                    }
                }
                holder1++;
            }

            //insertion sort
//             int n;
//    for (holder1 = holder1 + 1; holder1 < j1; holder1++)
//    {
//        n = holder1;
//        while (n > 0 && AllSongs[n] < AllSongs[n - 1])
//        {
//            strcpy(temp, AllSongs[n]);
//            strcpy(AllSongs[n], AllSongs[n - 1]);
//            strcpy(AllSongs[n - 1], temp);
//            n--;
//        }
//    }
            holder = j + 1;

            //artist index counts the number of artists there are in the array
            artistIndex++;
        }
    }


    //putting the last artist into the array for only artists to sort
    //Then putting it in a smaller array to help checks later
    strcpy(Artists[artistIndex], AllSongs[holder]);
    strcpy(lastartist[0], AllSongs[holder]);


    // sorting last songs
    int holder1;
    int j1;

//int n;
    //insertion sort
//    for (holder1 = holder1 + 1; holder1 < j1; holder1++)
//    {
//        n = holder1;
//        while (n > 0 && AllSongs[n] < AllSongs[n - 1])
//        {
//            strcpy(temp, AllSongs[n]);
//            strcpy(AllSongs[n], AllSongs[n - 1]);
//            strcpy(AllSongs[n - 1], temp);
//            n--;
//        }
//    }



//sorting all artist names
    for (int artistIndex1 = 0; artistIndex1 <= artistIndex; artistIndex1++) {

        for (int comparing = artistIndex1 + 1; comparing <= artistIndex; comparing++) {

            if (strcmp(Artists[artistIndex1], Artists[comparing]) > 0) {
                strcpy(temp, Artists[artistIndex1]);
                strcpy(Artists[artistIndex1], Artists[comparing]);
                strcpy(Artists[comparing], temp);
            }
        }
    }


    holder1 = holder + 1;
    j1 = i - 1;

    //This sorts the songs by the last artist
    while (holder1 <= j1){

        for (comparing = holder1 + 1; comparing <= j1; comparing++) {

            if (strcmp(AllSongs[holder1], AllSongs[comparing]) > 0) {
                strcpy(temp, AllSongs[holder1]);
                strcpy(AllSongs[holder1], AllSongs[comparing]);
                strcpy(AllSongs[comparing], temp);
            }
        }
        holder1++;
    }




    //printing sorted artist and songs section//////////////////////////////////////////////////////////////////////////

    int k;
    holder = 0;

    //loop for artist index, compare the value indexed by k in the artist array
    //if it is the same as string indexed by j in allsongs array do stuff
    for (k = 0; k <= artistIndex; k++) {

        //looping for all the songs
        for (j = 0; j <= rowsize; j++) {

            //checking if the line is empty if it is check if condition inside
            if (!(((strcmp(AllSongs[j], "\n")) != 0) && ((strcmp(AllSongs[j], "\r\n")) != 0) && ((strcmp(AllSongs[j], "\0")) != 0) && 1)) {


                //if artist name is the same as the artist currently indexed in allsongs array,
                //print it
                if ((strcmp(AllSongs[holder], Artists[k])) == 0) {

                    printf("%s\n",AllSongs[holder]);
                    for (int holder1 = holder + 1; holder1 <= j - 1; holder1++) {
                        printf("o %s\n",AllSongs[holder1]);
                    }

                    //checking if indexed artist is the last artist if so, then print this
                    if ((strcmp(AllSongs[holder], lastartist[0])) == 0){
                        for (int holder1 = holder + 1; holder1 <= i - 1; holder1++) {
                            printf("o %s\n",AllSongs[holder1]);
                        }
                    }

                    printf("\n");
                }

                //a check for the first artist in the file
                if ((strcmp(AllSongs[0], Artists[k])) == 0) {

                    printf("%s\n",AllSongs[0]);

                    for (int holder1 = 1; holder1 <= j - 1; holder1++) {
                        printf("o %s\n",AllSongs[holder1]);
                    }
                    printf("\n");

                    //increment k to stop for repeated printing
                    k++;
                }

                holder = j + 1;
            }
        }

    }




    //tokenising and putting into struct section////////////////////////////////////////////////////////////////////////


//copy into new array so main isn't messed up when tokenizing
    for ( j = 0; j <= rowsize; j++) {
        strcpy(Tokenise[j], AllSongs[j]);
    }

//Defined a struct array (from beginning)
    struct ArtistsAndSongs record[rowsize];

    char * item;
    int count;
    holder = 0;
    count = 0;

    // Read 2d array line by line and tokenise it
    for (j = 0; j <= rowsize; j++) {

        //if the line is empty put allsongs[holder] into first part of struct (artist name)
        if (!(((strcmp(AllSongs[j], "\n")) != 0) && ((strcmp(AllSongs[j], "\r\n")) != 0) && ((strcmp(AllSongs[j], "\0")) != 0) && 1)) {

            for (int l = holder + 1; l <= j - 1; l++) {

                strcpy(record[count].Artist_name, Tokenise[holder]); //artist name

                item = strtok(Tokenise[l], "***");
                strcpy(record[count].song, item); //song

                item = strtok(NULL, "**:");
                strcpy(record[count].time_minutes, item); //Get the minute(s)

                item = strtok(NULL, "\n");
                strcpy(record[count].time_seconds, item); //get the seconds(s)

                count++;
            }
            holder = j + 1;
        }

    }



    //calling shuffle function from header file
    shuffle(artistIndex, Artists, count, record);

    return 0;
}


void rules(void){
    printf("The format of the file is as follows:\n"
           "\n"
           "Artiste name\n"
           "Song title***Song duration\n"
           "Song title***Song duration\n"
           "...\n"
           "Song title***Song duration\n"
           "<blank line>\n"
           "Artiste name\n"
           "Song title***Song duration\n"
           "Song title***Song duration\n"
           "...\n"
           "Song title***Song duration\n"
           "<blank line>\n"
           "...\n"
           "\n"
           "Each song title comprises alphanumeric characters (letters, numbers and symbols)\n"
           "but does not contain the sub-string '***'.\n"
           "Song duration is in the form [m]m:ss, where [m]m denotes a one- or two-digit number of minutes\n"
           "and ss denotes a two-digit number of seconds.\n"
           "For testing purposes, at least two artistes should have three or more songs each.\n\n\n");
}

//reads in keyboard input and rowsize and returns the rowsize
int keyboard(char read[][50]){
    int i;

    while (fgets(read[i],50, stdin)) {
        //remove newline character
        char len = strlen(read[i]);
        if( read[i][len-1] == '\n' )
            read[i][len-1] = 0;
        i++;
    }

    return i;
}
