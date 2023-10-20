#ifndef _LAB_2_
#define _LAB_2_

#define MAX_TRANSITIONS 20
#define MAX_STATES 20

typedef struct
{
	char key;
	int toStateID;
} Transition;

typedef struct
{
	int ID;
	int numOfTransitions;
	int isFinal;
	Transition transitions[MAX_TRANSITIONS];
} State;

typedef struct
{
	int startStateID;
	int currentStateID;
	int numOfStates;
	char inputSymbol;
	State states[MAX_STATES];
} Automaton;

Automaton* createAutomaton(int startStateID);
int makeNextTransition(Automaton* dfa);
void setupAutomaton(Automaton* dfa, char newKey);
void addState(Automaton* dfa, State* newState);
void addTransition(Automaton* dfa, int fromStateID, char transitionKey, int toStateID);
State* createState(int finalState);
char* findUnrecognizedSymbols(Automaton* dfa, char* inputSymbols);
Automaton* setupAutomatonFromFile();

#endif

/*
1. Set up a blank Automaton
2. Set up states
3. Set up transitions
*/