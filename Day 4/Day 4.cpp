// Day 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <algorithm>
#include <iostream>
#include <string>
#include "inputs.h"
#include <map>

using namespace std;


bool sortFunc( std::string i, std::string j )
{
	auto first = i.substr( 1, 16 );
	auto second = j.substr( 1, 16 );

	return ( i < j );
}

int main()
{
	std::cout << "Day 4: Find the sleepy guard" << std::endl;

	auto data = inputs::data;
	//std::vector<std::string> data
	//{
	//	"[1518 - 11 - 01 00:00] Guard #10 begins shift ",
	//	"[1518 - 11 - 01 00:05] falls asleep			  ",
	//	"[1518 - 11 - 01 00:25] wakes up				  ",
	//	"[1518 - 11 - 01 00:30] falls asleep			  ",
	//	"[1518 - 11 - 01 00:55] wakes up				  ",
	//	"[1518 - 11 - 01 23:58] Guard #99 begins shift ",
	//	"[1518 - 11 - 02 00:40] falls asleep			  ",
	//	"[1518 - 11 - 02 00:50] wakes up				  ",
	//	"[1518 - 11 - 03 00:05] Guard #10 begins shift ",
	//	"[1518 - 11 - 03 00:24] falls asleep			  ",
	//	"[1518 - 11 - 03 00:29] wakes up				  ",
	//	"[1518 - 11 - 04 00:02] Guard #99 begins shift ",
	//	"[1518 - 11 - 04 00:36] falls asleep			  ",
	//	"[1518 - 11 - 04 00:46] wakes up				  ",
	//	"[1518 - 11 - 05 00:03] Guard #99 begins shift ",
	//	"[1518 - 11 - 05 00:45] falls asleep			  ",
	//	"[1518 - 11 - 05 00:55] wakes up				  "
	//};
	std::sort( data.begin(), data.end(), sortFunc );

	std::map<std::string, std::vector<int>> guardSleepCount;

	auto firstLine = data[0];
	std::string id;
	for( int i = 1; i < ( int )data.size() - 1; i++ )
	{
		auto date = firstLine.substr( 8, 7 );
		auto time = firstLine.substr( 16, 5 );
		auto hour = time.substr( 0, 2 );
		auto min = time.substr( 3, 2 );
		auto minute = std::stoi( min );
		auto type = firstLine[23];

		auto IsASleep = true;
		if( type == 'G' )
		{
			id = firstLine.substr( 30, 4 );
			IsASleep = false;
		}
		if( type == 'w' )
			IsASleep = false;
		if( type == 'f' )
			IsASleep = true;

		auto secondLine = data[i];
		auto date2 = secondLine.substr( 8, 7 );
		auto time2 = secondLine.substr( 16, 5 );
		auto min2 = time2.substr( 3, 2 );
		auto minute2 = std::stoi( min2 );
		auto type2 = secondLine[23];
		//std::string id2;
		//if (type == 'G')
		//	id2 = secondLine.substr(30, 4);

		if( type == 'G' )
		{
			auto guard = guardSleepCount.find( id );
			if( guard == guardSleepCount.end() )
			{
				std::vector<int> vect( 60, 0 );
				auto result = guardSleepCount.insert( std::make_pair( id, vect ) );
				guard = result.first;
			}
		}

		if( IsASleep )
		{
			auto guard = guardSleepCount.find( id );
			auto& sleepVect = guard->second;
			for( int j = minute; j < minute2; j++ )
			{
				sleepVect[j]++;
			}
		}
		firstLine = secondLine;
	}

	auto max = std::max_element( guardSleepCount.begin(), guardSleepCount.end(),
	                             []( const pair<std::string, std::vector<int>>& p1, const pair<std::string, std::vector<int>>& p2 )
	{
		auto p1Count = 0;
		for( auto& n : p1.second )
			p1Count += n;

		auto p2Count = 0;
		for( auto& n : p2.second )
			p2Count += n;

		return p1Count < p2Count;
	} );

	std::map<std::string, int> sums;
	for( auto x : guardSleepCount )
	{
		auto sum = 0;
		for( auto y : x.second )
			sum += y;

		sums.insert( std::make_pair( x.first, sum ) );
	}

	auto idNum = std::stoi( max->first );
	auto count = 0;
	for( auto& n : max->second )
		count += n;

	auto result2 = std::max_element( max->second.begin(), max->second.end() );
	auto pos = std::distance( max->second.begin(), result2 );
	//auto maxMinute = max->second[pos];
	auto part1 = idNum * pos;

	std::cout << "\nThe id * max minutes of sleep is : " << part1 << std::endl;

	auto maxCount = 0;
	auto guardID = -1;
	auto minute = -2;
	for( auto guard : guardSleepCount )
	{
		auto result = std::max_element( guard.second.begin(), guard.second.end() );
		auto pos = std::distance( guard.second.begin(), result );

		if( guard.second.at( pos ) > maxCount )
		{
			maxCount = guard.second.at( pos );
			guardID = std::stoi( guard.first );
			minute = ( int )pos;
		}
	}
	auto part2 = guardID * minute;
	std::cout << "\n\nPart 2: The check sum for the guard most frequently asleep on the same minute is: " << part2;

}



