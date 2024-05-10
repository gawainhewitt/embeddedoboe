#include "Oboe_samples.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>



// GUItool: begin automatically generated code
AudioSynthWavetable      wavetable1;     //xy=287,516
AudioEffectEnvelope      envelope1;      //xy=425,516
AudioAmplifier           amp1;           //xy=907,715
AudioOutputI2S           i2s1;           //xy=1202,720
AudioConnection          patchCord1(wavetable1, envelope1);
AudioConnection          patchCord2(envelope1, amp1);
AudioConnection          patchCord3(amp1, 0, i2s1, 0);
AudioConnection          patchCord4(amp1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=515,851
// GUItool: end automatically generated code




float freqnotes[] = {
16.35,      17.32,      18.35,      19.45,      20.60,      21.83,      23.12,      24.50,      25.96,      27.50,      29.14,      30.87, 
32.70,      34.65,      36.71,      38.89,      41.20,      43.65,      46.25,      49.00,      51.91,      55.00,      58.27,      61.74, 
65.41,      69.30,      73.42,      77.78,      82.41,      87.31,      92.50,      98.00,      103.83,     110.00,     116.54,     123.47, 
130.81,     138.59,     146.83,     155.56,     164.81,     174.61,     185.00,     196.00,     207.65,     220.00,     233.08,     246.94, 
261.63,     277.18,     293.66,     311.13,     329.63,     349.23,     369.99,     392.00,     415.30,     440.00,     466.16,     493.88, 
523.25,     554.37,     587.33,     622.25,     659.26,     698.46,     739.99,     783.99,     830.61,     880.00,     932.33,     987.77,       
1046.50,    1108.73,    1174.66,    1244.51,    1318.51,    1396.91,    1479.98,    1567.98,    1661.22,    1760.00,    1864.66,    1975.53, 
2093.00,    2217.46,    2349.32,    2489.02,    2637.02,    2793.83,    2959.96,    3135.96,    3322.44,    3520.00,    3729.31,    3951.07,      
4186.01,    4434.92,    4698.64,    4978.03};

const String noteNames[24]={"C","C#","D","D#","E","F","F#","G","G#","A","A#","B","C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};

String keyName = "C";
int keyPosition = 0;

int octave = 36;

const int numberOfSensors = 11;

byte major[] = {0, 4, 7, 12, 16, 19, 24, 28, 31, 36, 40};
byte minor[] = {0, 3, 7, 12, 15, 19, 24, 27, 31, 36, 39};
byte dom7[] = {0, 4, 7, 10, 12, 16, 19, 22, 24, 28, 31};
byte maj7[] = {0, 4, 7, 11, 12, 16, 19, 23, 24, 28, 31};
byte min7[] = {0, 3, 7, 10, 12, 15, 19, 22, 24, 27, 31};

byte chord[] = {0, 4, 7, 12, 16, 19, 24, 28, 31, 36, 40}; // default to major

int currentChord = 0;
int numChords = 5;

String chordTypeName = "";


void setupAudio() {

    AudioMemory(20);

    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5);

    wavetable1.setInstrument(Oboe);

    int wavetableAmplitude = 1;

    wavetable1.amplitude(wavetableAmplitude);

    int attackAmount = 3;

    envelope1.attack(attackAmount);


}

void playSound(int octave, int note) {
    switch(note) 
    {
        case 0:
            wavetable1.playFrequency(freqnotes[keyPosition + chord[note]+ octave]);
            envelope1.noteOn();
            break;
        case 1:
            wavetable1.playFrequency(freqnotes[keyPosition + chord[note] + octave]);
            envelope1.noteOn();
            break;
        case 2:
            wavetable1.playFrequency(freqnotes[keyPosition + chord[note] + octave]);
            envelope1.noteOn();
            break;
        case 3:
            wavetable1.playFrequency(freqnotes[keyPosition + chord[note] + octave]);
            envelope1.noteOn();
            break;
        case 4:
            wavetable1.playFrequency(freqnotes[keyPosition + chord[note] + octave]);
            envelope1.noteOn();
            break;
        case 5:
            wavetable1.playFrequency(freqnotes[keyPosition + chord[note] + octave]);
            envelope1.noteOn();
            break;
        case 6:
            wavetable1.playFrequency(freqnotes[keyPosition + chord[note] + octave]);
            envelope1.noteOn();
            break;
        case 7:
            wavetable1.playFrequency(freqnotes[keyPosition + chord[note] + octave]);
            envelope1.noteOn();
            break;
        case 8:
            wavetable1.playFrequency(freqnotes[keyPosition + chord[note] + octave]);
            envelope1.noteOn();
            break;
        case 9:
            wavetable1.playFrequency(freqnotes[keyPosition + chord[note] + octave]);
            envelope1.noteOn();
            break;
        case 10:
            wavetable1.playFrequency(freqnotes[keyPosition + chord[note] + octave]);
            envelope1.noteOn();
            break;
    }
}

void stopSound(int octave, int note) {
    switch(note) 
    {
        case 0:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 1:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 2:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 3:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 4:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 5:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 6:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 7:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 8:
            wavetable1.stop();
            envelope1.noteOff();
            break;
        case 9:
            wavetable1.stop();
            envelope1.noteOff();
             break;
        case 10:
            wavetable1.stop();
            envelope1.noteOff();
             break;
    }
}

void changeChord(int chordType) {
    
    switch(chordType) {
        case 0: 
        for (uint8_t i=0; i < numberOfSensors; i++) {
        chord[i] = major[i];
        chordTypeName = "";
        }
        break;
        case 1: 
        for (uint8_t i=0; i < numberOfSensors; i++) {
        chord[i] = minor[i];
        chordTypeName = "Minor";
        }
        break;
        case 2: 
        for (uint8_t i=0; i < numberOfSensors; i++) {
        chord[i] = dom7[i];
        chordTypeName = "Dom7";
        }
        break;
        case 3: 
        for (uint8_t i=0; i < numberOfSensors; i++) {
        chord[i] = maj7[i];
        chordTypeName = "Maj7";
        }
        break;
        case 4: 
        for (uint8_t i=0; i < numberOfSensors; i++) {
        chord[i] = min7[i];
        chordTypeName = "min7";
        }
    }
}
