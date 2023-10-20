#include "lab2.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int inputAlphabetLen = 26;
const char* filename = "E:\\Uni\\System Programming\\input.txt";

int makeNextTransition(Automaton* dfa)
{
	int transitionID;
	State* currentState = &dfa->states[dfa->currentStateID];
	for (transitionID = 0; transitionID < currentState->numOfTransitions; transitionID++)
	{
		if (currentState->transitions[transitionID].key == dfa->inputSymbol)
		{
			dfa->currentStateID = currentState->transitions[transitionID].toStateID;
			return 0;  // return 0 if the transition has been made
		}
	}

	if (currentState->isFinal == 1)
	{
		return 1;  // return 1 if the automaton stopped in a final state
	}

	return 2;  // return 2 if the automaton stopped in a non-final state 
}

void addState(Automaton* dfa, State* newState)
{
	newState->ID = dfa->numOfStates;
	dfa->states[dfa->numOfStates] = *newState;
	dfa->numOfStates++;
}

void addTransition(Automaton* dfa, int fromStateID, char transitionKey, int toStateID)
{
	State* state = &dfa->states[fromStateID];
	state->transitions[state->numOfTransitions].key = transitionKey;
	state->transitions[state->numOfTransitions].toStateID = toStateID;
	state->numOfTransitions++;
}

State* createState(int finalState)
{
	State* newState = (State*)malloc(sizeof(State));
	newState->isFinal = finalState;
	newState->ID = -1;
	newState->numOfTransitions = 0;

	return newState;
}

Automaton* createAutomaton(int startStateID)
{
	Automaton* dfa = (Automaton*)malloc(sizeof(Automaton));
	dfa->numOfStates = 0;
	dfa->startStateID = startStateID;
	dfa->currentStateID = dfa->startStateID;

	return dfa;
}

void setupAutomaton(Automaton* dfa, char newKey)
{
	dfa->currentStateID = dfa->startStateID;
	dfa->inputSymbol = newKey;
}

char* findUnrecognizedSymbols(Automaton* dfa, char* inputSymbols)
{
	char unrecognizedSymbols[26];

	int currentTransitionSuccessful;
	int unrecognizedSymbolsCounter = 0;

	for (int i = 0; i < inputAlphabetLen; i++)
	{
		setupAutomaton(dfa, inputSymbols[i]);
		do
		{
			currentTransitionSuccessful = makeNextTransition(dfa);
		} while (currentTransitionSuccessful == 0);

		if (currentTransitionSuccessful == 2)
		{
			unrecognizedSymbols[unrecognizedSymbolsCounter++] = inputSymbols[i];
		}
	}

	return unrecognizedSymbols;
}

Automaton* setupAutomatonFromFile()
{
	Automaton* dfa = createAutomaton(-1);

	FILE* file = fopen(filename, "r");
	int maxLines = 24;
	int maxLineLen = 10;

	/*if (file == NULL)
	{
		printf("Error while trying to open the file.");
		return dfa;
	}*/

	char** lines = (char**)malloc(maxLines * sizeof(char*));
	for (int i = 0; i < maxLines; i++)
	{
		lines[i] = (char*)malloc(maxLineLen * sizeof(char));
	}

	/*if (lines == NULL)
	{
		printf("Memory allocation error.");
		return dfa;
	}*/

	int lineCount = 0;
	while (fgets(lines[lineCount], maxLineLen, file) != NULL && lineCount < maxLines)
	{
		lineCount++;
	}
	fclose(file);

	// setting up the automaton from user input
	inputAlphabetLen = lines[0][0];


	dfa->startStateID = (lines[2][0] - '0');
	int statesLen = (lines[1][0] - '0');
	int finalStatesLen = (lines[3][0] - '0');
	int finalStatesIDs[MAX_STATES];
	for (int i = 0; i < finalStatesLen; i++)
	{
		finalStatesIDs[i] = (lines[3][(i + 1) * 2] - '0');
	}

	State* currentState;
	for (int i = 0; i < statesLen; i++)
	{
		int isFinalState = 0;
		for (int j = 0; j < finalStatesLen; j++)
		{
			if (i == finalStatesIDs[j])
			{
				isFinalState = 1;
				break;
			}
		}
		
		currentState = createState(isFinalState);
		addState(dfa, currentState);
	}

	for (int i = 4; i < lineCount; i++)
	{
		int fromStateID = (lines[i][0] - '0');
		int toStateID = (lines[i][4] - '0');
		char key = lines[i][2];

		addTransition(dfa, fromStateID, key, toStateID);
	}

	return dfa;
}

void main()
{
	char inputAlphabet[26];
	printf("Enter the input alphabet: ");
	for (int i = 0; i < inputAlphabetLen; i++)
	{
		scanf("%c", &inputAlphabet[i]);
	}
	
	// char inputAlphabet[] = { 'a', 'b', 'c', 'd', 'e' };


	Automaton* dfa = setupAutomatonFromFile();
	char* unrecognizedSymbols = findUnrecognizedSymbols(dfa, inputAlphabet);

	for (int i = 0; i < inputAlphabetLen; i++)
	{
		if (unrecognizedSymbols[i] < 'a' || unrecognizedSymbols[i] > 'z')
		{
			break;
		}
		else
		{
			printf("%c ", unrecognizedSymbols[i]);
		}
	}
}
