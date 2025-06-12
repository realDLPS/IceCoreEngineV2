#pragma once

#include <array>

constexpr float DEFAULTFONTSIZE = 16.0f;
constexpr TextureFilter FONTFILTERING = TEXTURE_FILTER_TRILINEAR;

constexpr int ASCIISTART = 32, ASCIIEND = 126;
constexpr int ASCIICOUNT = ASCIIEND - ASCIISTART + 1;

constexpr int ADDITIONALCODEPOINTCOUNT = 6;
constexpr int ADDITIONALCODEPOINTS[ADDITIONALCODEPOINTCOUNT] = 
{ 
	0x00C5,
	0x00E5,
	0x00C4, 
	0x00E4, 
	0x00D6, 
	0x00F6
};

constexpr int CODEPOINTCOUNT = ASCIICOUNT + ADDITIONALCODEPOINTCOUNT;

constexpr std::array<int, CODEPOINTCOUNT> GenerateCodepoints() {
    std::array<int, CODEPOINTCOUNT> codepoints{};

    for (int i = 0; i < ASCIICOUNT; ++i) {
        codepoints[i] = ASCIISTART + i;
    }

    for (int i = 0; i < ADDITIONALCODEPOINTCOUNT; ++i) {
        codepoints[ASCIICOUNT + i] = ADDITIONALCODEPOINTS[i];
    }

    return codepoints;
}

constexpr std::array<int, CODEPOINTCOUNT> CODEPOINTSCPP = GenerateCodepoints();