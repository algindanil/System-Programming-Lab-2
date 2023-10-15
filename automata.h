#ifndef _DFA_H_
#define _DFA_H_

#define MAX_TRANSITIONS 50
#define MAX_STATES 100


typedef struct
{
	int (*condition)(char);
	int toStateID;
} Transition;

typedef struct
{
	int ID;
	int hasAction;
	int numOfTranisitions;
	bool isFinal;
	char actionName[256];
	Transition transitions[MAX_TRANSITIONS];
	int defaultToStateID;
} State;

typedef struct
{
	int startStateID;
	int currentStateID;
	int numberOfStates;
	State* states[MAX_STATES];
} Automaton;

Automaton createDFA();
int makeNextTransition(Automaton* dfa, char c);
void reset(Automaton* dfa);
void addState(Automaton* pDFA, State* newState);
void addTransition(Automaton* dfa, int fromStateID, int(*condition)(char), int toStateID);
State* createState(int hasAction, bool finalState, char* actionName);

#endif
