#indlude "automata.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int makeNextTransition(Automaton* dfa, char c)
{
	int transitionID;
	State* pCurrentState = dfa->states[dfa->currentStateID];
	for (transitionID = 0; transitionID < pCurrentState->numOfTransitions; transitionID++)
	{
		if (pCurrentState->transitions[transitionID].condition(c))
		{
			dfa->currentStateID = pCurrentState->transitions[transitionID].toStateID;
			return 0;  // returns 0 if the transition had been successful
		}
	}

	if (pCurrentState->isFinal)
	{
		return 1;  // returns 1 if the state that has no transitions for the symbol is final
	}

	dfa->currentStateID = pCurrentState->defaultToStateID;
	return 2;  // returns 2 if the transition failed and the automaton was reset to the default state
}

void addState(Automaton* pDFA, State* newState)
{
	newState->ID = pDFA->numberOfStates;
	pDFA->states[pDFA->numberOfStates] = newState;
	pDFA->numberOfStates++;
}

void addTransition(Automaton* dfa, int fromStateID, int(*condition)(char), int toStateID)
{
	State* state = dfa->states[fromStateID];
	state->transitions[state->numOfTransitions].condition = condition;
	state->transitions[state->numOfTransitions].toStateID = toStateID;
	state->numOfTransitions++;
}

State* createState(int hasAction, bool finalState, char* actionName)
{
	State* newState = (State*)malloc(sizeof(State));
	strcpy(newState->actionName, actionName);
	newState->isFinal = finalState;
	newState->defaultToStateID = -1;
	newState->hasAction = hasAction;
	newState->ID = -1;
	newState->numOfTransitions = 0;

	return newState;
}

Automaton* createDFA()
{
	Automaton* dfa = (Automaton*)malloc(sizeof(Automaton));
	dfa->numOfStates = 0;
	dfa->startStateID = -1;
	dfa->currentStateID = -1;
	return dfa;
}

void reset(Automaton* dfa)
{
	dfa->currentStateID = dfa->startStateID;
}

char* findUnrecognizedSymbols(Automaton* dfa, char* symbols)
{
	symbolsLen = sizeof(symbols) / sizeof(symbols[0])
	char* unrecognizedSymbols = char[symbolsLen];

	int currentTransitionSuccessful;
	int unrecognizedSymbolsCounter = 0;

	for (int i = 0; i < symbolsLen; i++)
	{
		do {
			currentTransitionSuccessful = makeNextTransition(dfa, symbols[i]);
		} while (currentTransitionSuccessful == 0);

		if (currentTransitionSuccessful == 2)
		{
			unrecognizedSymbols[unrecognizedSymbolsCounter++] = symbols[i];
		}
	}

	reset(dfa);
	return unrecognizedSymbols;
}

void main()
{
	
}