#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>

class Dirt;
class Object;
class FrackMan;
class Agent;

int randInt(int min, int max); //at bottom of StudentWorld
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	enum ObjectName { FrackMan_, Boulder_, Oil_, Gold_, Sonar_, Water_, RegularProtester_, DroppedGold_, Squirt_, HardcoreProtester_};
	StudentWorld(std::string assetDir);
	~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	int annoyAllNearbyAgents(Object* annoyer, int points, int radius, bool frackerIsImmune = true);
	void give(ObjectName objectName, Object* reciever = nullptr);
	void revealAllNearbyObjects(int x, int y, int radius);
	Object* findNearbyFrackMan(Object* a, int radius) const; //In man is within radius, return him if not null 
	Object* findNearbyProtestor(Object* a, int radius);
	bool facingTowardFrackMan(Object* a);
	void addActor(ObjectName objectName, int number = 1); // adds object base on enumerator
	bool canActorMoveTo(Object* a, int x, int y); //checks boundaries and boulders
	bool isDirtAt(int x, int y);
	bool isDirtAround(int x, int y); //different from dirt at as it checks the 4x4 square using x,y as bottom left
	void clearDirt(int x, int y, bool sound); //given the actors coordinates delete all dirt in 4x4
	double distanceBetween(Object* a1, int x, int y) const;
	Object* objectCollided(Object* actor, int x, int y);
	int determineFirstMoveTo(Object* p1, int x, int y, bool& toFrackMan, int maxMoves = -1);
	int determineDirTo(int x, int y, bool toFrackMan = false);
	
private:
	bool fillDistanceArrayTo(Object* p1, int x, int y, bool toFrackMan, int maxMoves = -1);
	void setDisplayText();
	bool withinMineShaft(int x, int y);
	bool closeToObjects(int x, int y);
	int m_DistanceToExit[64][64]; 
	int m_DistanceToFrackMan[64][64];
	Dirt* m_Dirt[64][64];
	std::vector <Object*> m_Actors;
	FrackMan* m_FrackMan;
	int m_BarrelsLeft;
	int m_MaxProtestors;
	int m_currentProtestors;
	int m_ProtestorsAddWaitTime;
	int m_currentTimeSinceAdd;
};

#endif // STUDENTWORLD_H_

/*
It was ambigious whether to have the guy kill himself immediately without any other actor doing anthign, but the two extra lines of code this needed seem unneccessary
The math logic was slightly ambigious but i just used general precedence operations
In the given game, the protester didnt always turn perpendicular right after it spawns when the specafications said if it was a t a perpendicular and turn and hadnt done a intential one in the last 200 ticks to turn
It was unspecified but I copied what the program seemed to do and delete the dirt the tick after he moved there.
*/