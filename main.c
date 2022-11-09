#include <stdio.h>
#include <assert.h>
#include "main.h"

void ColorPairToString(const ColorPair* colorPair, char* buffer) {
    sprintf(buffer, "%s + %s", MajorColorNames[colorPair->majorColor], MinorColorNames[colorPair->minorColor]);
}

ColorPair GetColorFromPairNumber(int pairNumber) {
    ColorPair colorPair;
    int zeroBasedPairNumber = pairNumber - 1;
    colorPair.majorColor = (enum MajorColor)(zeroBasedPairNumber / numberOfMinorColors);
    colorPair.minorColor = (enum MinorColor)(zeroBasedPairNumber % numberOfMinorColors);
    return colorPair;
}

int GetPairNumberFromColor(const ColorPair* colorPair) {
    return colorPair->majorColor * numberOfMinorColors + colorPair->minorColor + 1;
}

void testNumberToPair(int pairNumber, enum MajorColor expectedMajor, enum MinorColor expectedMinor) {
    ColorPair colorPair = GetColorFromPairNumber(pairNumber);
    char colorPairNames[MAX_COLORPAIR_NAME_CHARS];
    ColorPairToString(&colorPair, colorPairNames);
    printf(" %s\n", colorPairNames);
    assert(colorPair.majorColor == expectedMajor);
    assert(colorPair.minorColor == expectedMinor);
}

void testPairToNumber(enum MajorColor major, enum MinorColor minor, int expectedPairNumber){
    ColorPair colorPair;
    colorPair.majorColor = major;
    colorPair.minorColor = minor;
    int pairNumber = GetPairNumberFromColor(&colorPair);
    printf("Pair number %d: ", pairNumber);
    assert(pairNumber == expectedPairNumber);
}

int main() {
	FILE *fp;
    fp = freopen("Color_Coding_Manual.txt", "w+", stdout);
	static int offset = 1;
	for(int ColorMajor = 0; ColorMajor < numberOfMinorColors; ColorMajor++) {
		for(int ColorMinor = 0; ColorMinor < numberOfMinorColors; ColorMinor++) {
		testPairToNumber(ColorMajor, ColorMinor, ColorMinor + offset);
		testNumberToPair(ColorMinor + offset, ColorMajor, ColorMinor);
		}offset += 5;
	}fclose(fp);
	
    return 0;}
