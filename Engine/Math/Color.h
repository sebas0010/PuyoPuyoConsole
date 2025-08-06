#pragma once

// »ö»ó.
enum class Color : int
{
	Blue = 1,
	Green = 2,
	Red = 4,
	Yellow = Green | Red,
	Magneta = Blue | Red,
	White = Red | Green | Blue,
	Intensity = 8,
	BackGroundRed = Red << 4,
	BackGroundIntensity = Intensity << 4,
	BackGroundRedIntensity = BackGroundRed | BackGroundIntensity
};