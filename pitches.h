#include <pitches.h>

// Star Wars

int melody1[] = {
    NOTE_AS4, NOTE_AS4, NOTE_AS4,
    NOTE_F5, NOTE_C6,
    NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
    NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
    NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5, NOTE_C5,
    NOTE_F5, NOTE_C6,
    NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,

    NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
    NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5,
    NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,
    NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_C5,
    NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,

    NOTE_C6, NOTE_G5, NOTE_G5, REST, NOTE_C5,
    NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,
    NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C6, NOTE_C6,
    NOTE_F6, NOTE_DS6, NOTE_CS6, NOTE_C6, NOTE_AS5, NOTE_GS5, NOTE_G5, NOTE_F5,
    NOTE_C6};

int durations1[] = {
    9, 9, 9,
    2, 2,
    9, 9, 9, 2, 4,
    9, 9, 9, 2, 4,
    9, 9, 9, 2, 9, 9, 9,
    2, 2,
    9, 9, 9, 2, 4,

    9, 9, 9, 2, 4,
    9, 9, 9, 2, 8, 8,
    3, 8, 8, 8, 8, 8,
    9, 9, 9, 3, 8, 3, 8, 8,
    3, 8, 8, 8, 8, 8,

    8, 16, 2, 8, 8,
    3, 8, 8, 8, 8, 8,
    8, 8, 8, 3, 8, 3, 8, 8,
    3, 8, 3, 8, 3, 8, 3, 8,
    1};

// Korobeiniki (Tetris)
int melody2[] = {
    NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4,
    NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
    NOTE_C5, NOTE_A4, NOTE_A4,

    NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5,
    NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
    NOTE_C5, NOTE_A4, NOTE_A4, REST,

    NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4,
    NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
    NOTE_C5, NOTE_A4, NOTE_A4,

    NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5,
    NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
    NOTE_C5, NOTE_A4, NOTE_A4, REST,

    NOTE_E5, NOTE_C5,
    NOTE_D5, NOTE_B4,
    NOTE_C5, NOTE_A4,
    NOTE_GS4, NOTE_B4, REST,
    NOTE_E5, NOTE_C5,
    NOTE_D5, NOTE_B4,
    NOTE_C5, NOTE_E5, NOTE_A5,
    NOTE_GS5};

int durations2[] = {
    4, 8, 8, 4, 8, 8,
    3, 8, 4, 8, 8,
    4, 8, 8, 4, 4,
    4, 4, 2,

    3, 8, 4, 8, 8,
    3, 8, 4, 8, 8,
    4, 8, 8, 4, 4,
    4, 4, 2, 4,

    4, 8, 8, 4, 8, 8,
    3, 8, 4, 8, 8,
    4, 8, 8, 4, 4,
    4, 4, 2,

    4, 8, 4, 8, 8,
    4, 8, 4, 8, 8,
    4, 8, 8, 4, 4,
    4, 4, 4, 4,

    2, 2,
    2, 2,
    2, 2,
    2, 4, 8,
    2, 2,
    2, 2,
    4, 4, 2,
    2};

// Marios Bros

int melody3[] = {
    NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
    NOTE_G5, REST, NOTE_G4, REST,
    NOTE_C5, NOTE_G4, REST, NOTE_E4,
    NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
    REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,
    NOTE_C5, NOTE_G4, REST, NOTE_E4,
    NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
    REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,

    REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_E5,
    REST, NOTE_GS4, NOTE_A4, NOTE_C4, REST, NOTE_A4, NOTE_C5, NOTE_D5,
    REST, NOTE_DS5, REST, NOTE_D5,
    NOTE_C5, REST,

    REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_E5,
    REST, NOTE_GS4, NOTE_A4, NOTE_C4, REST, NOTE_A4, NOTE_C5, NOTE_D5,
    REST, NOTE_DS5, REST, NOTE_D5,
    NOTE_C5, REST,

    NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5,
    NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,

    NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5, NOTE_E5,
    REST,
    NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5,
    NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
    NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
    NOTE_G5, REST, NOTE_G4, REST,
    NOTE_C5, NOTE_G4, REST, NOTE_E4,

    NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
    REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,

    NOTE_C5, NOTE_G4, REST, NOTE_E4,
    NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
    REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,

    NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
    NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
    NOTE_D5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,

    NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
    NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
    NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
    NOTE_B4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
    NOTE_C5, NOTE_E4, NOTE_E4, NOTE_C4,

    NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
    NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
    NOTE_D5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,

    NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
    NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
    NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
    NOTE_B4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
    NOTE_C5, NOTE_E4, NOTE_E4, NOTE_C4,
    NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5, NOTE_E5,
    REST,

    NOTE_C5, NOTE_C5, NOTE_C5, REST, NOTE_C5, NOTE_D5,
    NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
    NOTE_E5, NOTE_E5, REST, NOTE_E5, REST, NOTE_C5, NOTE_E5,
    NOTE_G5, REST, NOTE_G4, REST,
    NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
    NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
    NOTE_D5, NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5,

    NOTE_E5, NOTE_C5, NOTE_A4, NOTE_G4,
    NOTE_E5, NOTE_C5, NOTE_G4, REST, NOTE_GS4,
    NOTE_A4, NOTE_F5, NOTE_F5, NOTE_A4,
    NOTE_B4, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5,
    NOTE_C5, NOTE_E4, NOTE_E4, NOTE_C4,

    // Game over sound
    NOTE_C5, NOTE_G4, NOTE_E4,
    NOTE_A4, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_AS4, NOTE_GS4,
    NOTE_G4, NOTE_D4, NOTE_E4};

int durations3[] = {
    8, 8, 8, 8, 8, 8, 8,
    4, 4, 8, 4,
    4, 8, 4, 4,
    4, 4, 8, 4,
    8, 8, 8, 4, 8, 8,
    8, 4, 8, 8, 4,
    4, 8, 4, 4,
    4, 4, 8, 4,
    8, 8, 8, 4, 8, 8,
    8, 4, 8, 8, 4,

    4, 8, 8, 8, 4, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    4, 4, 8, 4,
    2, 2,

    4, 8, 8, 8, 4, 8,
    8, 8, 8, 8, 8, 8, 8, 8,
    4, 4, 8, 4,
    2, 2,

    8, 4, 8, 8, 8, 4,
    8, 4, 8, 2,

    8, 4, 8, 8, 8, 8, 8,
    1,
    8, 4, 8, 8, 8, 4,
    8, 4, 8, 2,
    8, 8, 8, 8, 8, 8, 4,
    4, 4, 4, 4,
    4, 8, 4, 4,

    4, 4, 8, 4,
    8, 8, 8, 4, 8, 8,
    8, 4, 8, 8, 4,

    4, 8, 4, 4,
    4, 4, 8, 4,
    8, 8, 8, 4, 8, 8,
    8, 4, 8, 8, 4,

    8, 4, 8, 4, 4,
    8, 4, 8, 2,
    8, 8, 8, 8, 8, 8,

    8, 4, 8, 2,
    8, 4, 8, 4, 4,
    8, 4, 8, 2,
    8, 4, 8, 8, 8, 8,
    8, 4, 8, 2,

    8, 4, 8, 4, 4,
    8, 4, 8, 2,
    8, 8, 8, 8, 8, 8,

    8, 4, 8, 2,
    8, 4, 8, 4, 4,
    8, 4, 8, 2,
    8, 4, 8, 8, 8, 8,
    8, 4, 8, 2,
    8, 4, 8, 8, 8, 8, 8,
    1,

    8, 4, 8, 8, 8, 4,
    8, 4, 8, 2,
    8, 8, 8, 8, 8, 8, 4,
    4, 4, 4, 4,
    8, 4, 8, 4, 4,
    8, 4, 8, 2,
    8, 8, 8, 8, 8, 8,

    8, 4, 8, 2,
    8, 4, 8, 4, 4,
    8, 4, 8, 2,
    8, 4, 8, 8, 8, 8,
    8, 4, 8, 2,

    // game over sound
    4, 4, 4,
    8, 8, 8, 8, 8, 8,
    8, 8, 2};

// Pacman

int melody4[] = {

    NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5,
    NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_C5,
    NOTE_C6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_G6, NOTE_E6,

    NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_B5,
    NOTE_FS5, NOTE_DS5, NOTE_DS5, NOTE_E5, NOTE_F5,
    NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_B5};

int durations4[] = {
    16, 16, 16, 16,
    32, 16, 8, 16,
    16, 16, 16, 32, 16, 8,

    16, 16, 16, 16, 32,
    16, 8, 32, 32, 32,
    32, 32, 32, 32, 32, 16, 8};

// Pirates of the Caribbean

int melody5[] = {
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
    NOTE_A4, NOTE_G4, NOTE_A4, REST,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
    NOTE_A4, NOTE_G4, NOTE_A4, REST,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
    NOTE_D5, NOTE_E5, NOTE_A4, REST,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
    NOTE_C5, NOTE_A4, NOTE_B4, REST,

    NOTE_A4, NOTE_A4,
    // Repeat of first part
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
    NOTE_A4, NOTE_G4, NOTE_A4, REST,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, REST,
    NOTE_A4, NOTE_G4, NOTE_A4, REST,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, REST,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, REST,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, REST,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, REST,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, REST,
    NOTE_D5, NOTE_E5, NOTE_A4, REST,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, REST,
    NOTE_C5, NOTE_A4, NOTE_B4, REST,
    // End of Repeat

    NOTE_E5, REST, REST, NOTE_F5, REST, REST,
    NOTE_E5, NOTE_E5, REST, NOTE_G5, REST, NOTE_E5, NOTE_D5, REST, REST,
    NOTE_D5, REST, REST, NOTE_C5, REST, REST,
    NOTE_B4, NOTE_C5, REST, NOTE_B4, REST, NOTE_A4,

    NOTE_E5, REST, REST, NOTE_F5, REST, REST,
    NOTE_E5, NOTE_E5, REST, NOTE_G5, REST, NOTE_E5, NOTE_D5, REST, REST,
    NOTE_D5, REST, REST, NOTE_C5, REST, REST,
    NOTE_B4, NOTE_C5, REST, NOTE_B4, REST, NOTE_A4};

int durations5[] = {
    8, 8, 4, 8, 8,
    8, 8, 4, 8, 8,
    8, 8, 4, 8, 8,
    8, 8, 4, 8,

    8, 8, 4, 8, 8,
    8, 8, 4, 8, 8,
    8, 8, 4, 8, 8,
    8, 8, 4, 8,

    8, 8, 4, 8, 8,
    8, 8, 4, 8, 8,
    8, 8, 4, 8, 8,
    8, 8, 8, 4, 8,

    8, 8, 4, 8, 8,
    4, 8, 4, 8,
    8, 8, 4, 8, 8,
    8, 8, 4, 4,

    4, 8,
    // Repeat of First Part
    8, 8, 4, 8, 8,
    8, 8, 4, 8, 8,
    8, 8, 4, 8,

    8, 8, 4, 8, 8,
    8, 8, 4, 8, 8,
    8, 8, 4, 8, 8,
    8, 8, 4, 8,

    8, 8, 4, 8, 8,
    8, 8, 4, 8, 8,
    8, 8, 4, 8, 8,
    8, 8, 8, 4, 8,

    8, 8, 4, 8, 8,
    4, 8, 4, 8,
    8, 8, 4, 8, 8,
    8, 8, 4, 4,
    // End of Repeat

    4, 8, 4, 4, 8, 4,
    8, 8, 8, 8, 8, 8, 8, 8, 4,
    4, 8, 4, 4, 8, 4,
    8, 8, 8, 8, 8, 2,

    4, 8, 4, 4, 8, 4,
    8, 8, 8, 8, 8, 8, 8, 8, 4,
    4, 8, 4, 4, 8, 4,
    8, 8, 8, 8, 8, 2};

// Harry Potter

int melody6[] = {
    REST, NOTE_D4,
    NOTE_G4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_D5,
    NOTE_C5,
    NOTE_A4,
    NOTE_G4, NOTE_AS4, NOTE_A4,
    NOTE_F4, NOTE_GS4,
    NOTE_D4,
    NOTE_D4, REST, NOTE_D4,

    NOTE_G4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_D5,
    NOTE_F5, NOTE_E5,
    NOTE_DS5, NOTE_B4,
    NOTE_DS5, NOTE_D5, NOTE_CS5,
    NOTE_CS4, NOTE_B4,
    NOTE_G4,
    NOTE_AS4,

    NOTE_D5, NOTE_AS4,
    NOTE_D5, NOTE_AS4,
    NOTE_DS5, NOTE_D5,
    NOTE_CS5, NOTE_A4,
    NOTE_AS4, NOTE_D5, NOTE_CS5,
    NOTE_CS4, NOTE_D4,
    NOTE_D5,
    REST, NOTE_AS4,

    NOTE_D5, NOTE_AS4,
    NOTE_D5, NOTE_AS4,
    NOTE_F5, NOTE_E5,
    NOTE_DS5, NOTE_B4,
    NOTE_DS5, NOTE_D5, NOTE_CS5,
    NOTE_CS4, NOTE_AS4,
    NOTE_G4};

int durations6[] = {
    2, 4,
    3, 8, 4,
    2, 4,
    1.33,
    1.33,
    3, 8, 4,
    2, 4,
    1.33,
    4, 4, 4,

    3, 8, 4,
    2, 4,
    2, 4,
    2, 4,
    3, 8, 4,
    2, 4,
    1,
    4,

    2, 4,
    2, 4,
    2, 4,
    2, 4,
    3, 8, 4,
    2, 4,
    1,
    4, 4,

    2, 4,
    2, 4,
    2, 4,
    2, 4,
    3, 8, 4,
    2, 4,
    1};
