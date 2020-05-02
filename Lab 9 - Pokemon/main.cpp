#include "BSTInterface.h"  
#include "BST.h"           
#include "SetInterface.h"
#include "Set.h"
#include "HashMapInterface.h"
#include "HashMap.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char* argv[]) {
    VS_MEM_CHECK            // enable memory leak check

    // set up input and output files and read them
        if (argc < 3) {
            cerr << "Please provide name of input and output files";
            return 1;
        }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    HashMap<string, string> pokemon;
    HashMap<string, string> moves;
    HashMap<string, Set<string>> effectivities;
    HashMap<string, Set<string>> ineffectivities;

    // read input to map
    string command = "";
    string line = "";

    while (in >> command) {
        // Set: <item> { <item>}
        if (command == "Set:") { 
            Set<string> set;
            string setItem = "";
            getline(in, line);
            stringstream ss(line);
            while (ss >> setItem)  set.insert(setItem);
            out << command << line << endl;
            out << "  [" << set << "]" << endl;
        }
        // Pokemon: <pokemon> <AType>
        if (command == "Pokemon:") {
            string pokemonName = "";
            string pokemonType = "";
            in >> pokemonName >> pokemonType;
            pokemon[pokemonName] = pokemonType;
            out << command << " " << pokemonName << " " << pokemonType << endl;
        }
        // Move: <move> <Move_Type>
        if (command == "Move:") {
            string moveName = "";
            string moveType = "";
            in >> moveName >> moveType;
            moves[moveName] = moveType;
            out << command << " " << moveName << " " << moveType << endl;
        }
        // Effective: <attack> <PType>{ <PType>}
        if (command == "Effective:") {
            string attackName = "";
            string setItem = "";
            getline(in, line);
            stringstream ss(line);
            ss >> attackName;
            while (ss >> setItem) effectivities[attackName].insert(setItem);
            out << command << line << endl;
        }
        // Ineffective: <attack> <PType>{ <PType>}
        if (command == "Ineffective:") {
            string attackName = "";
            string setItem = "";
            getline(in, line);
            stringstream ss(line);
            ss >> attackName;
            while (ss >> setItem) ineffectivities[attackName].insert(setItem);
            out << command << line << endl;
        }
        // Pokemon
        if (command == "Pokemon") {
            out << endl << command << ": " << pokemon.size() << "/" << pokemon.max_size();
            out << pokemon << endl;
        }
        // Moves
        if (command == "Moves") {
            out << endl << command << ": " << moves.size() << "/" << moves.max_size();
            out << moves << endl;
        }
        // Effectivities
        if (command == "Effectivities") {
            out << endl << command << ": " << effectivities.size() << "/" << effectivities.max_size();
            out << effectivities << endl;
        }
        // Ineffectivities
        if (command == "Ineffectivities") {
            out << endl << command << ": " << ineffectivities.size() << "/" << ineffectivities.max_size();
            out << ineffectivities << endl;
        }
        // Battle: <P1> <A1> <P2> <A2>
        if (command == "Battle:") {
            string pokemon1, pokemon2;
            string attack1, attack2;
            getline(in, line);
            stringstream ss(line);
            ss >> pokemon1;
            ss >> attack1;
            ss >> pokemon2;
            ss >> attack2;

            int damageAToB = effectivities[moves[attack1]].count(pokemon[pokemon2]) - ineffectivities[moves[attack1]].count(pokemon[pokemon2]);
            int damageBToA = effectivities[moves[attack2]].count(pokemon[pokemon1]) - ineffectivities[moves[attack2]].count(pokemon[pokemon1]);
            out << endl << "Battle: " << pokemon1 << " " << attack1 << " " << pokemon2 << " " << attack2 << endl;
            out << "  " << pokemon1 << "(" << attack1 << ")" << " vs " << pokemon2 << "(" << attack2 << ")" << endl;
            
            // tie
            if ((damageAToB - damageBToA) == 0) {
                if (effectivities[moves[attack1]].count(pokemon[pokemon2]) == 1) {
                    out << "  " << pokemon1 << "'s " << attack1 << " is super effective against " << pokemon2 << endl;
                }
                else if (ineffectivities[moves[attack1]].count(pokemon[pokemon2]) == 1) {
                    out << "  " << pokemon1 << "'s " << attack1 << " is ineffective against " << pokemon2 << endl;
                }
                else if (effectivities[moves[attack1]].count(pokemon[pokemon2]) == 0 && ineffectivities[moves[attack1]].count(pokemon[pokemon2]) == 0) {
                    out << "  " << pokemon1 << "'s " << attack1 << " is effective against " << pokemon2 << endl;
                }
                if (effectivities[moves[attack2]].count(pokemon[pokemon1]) == 1) {
                    out << "  " << pokemon2 << "'s " << attack2 << " is super effective against " << pokemon1 << endl;
                }
                else if (ineffectivities[moves[attack2]].count(pokemon[pokemon1]) == 1) {
                    out << "  " << pokemon2 << "'s " << attack2 << " is ineffective against " << pokemon1 << endl;
                }
                else if (effectivities[moves[attack2]].count(pokemon[pokemon1]) == 0 && ineffectivities[moves[attack2]].count(pokemon[pokemon1]) == 0) {
                    out << "  " << pokemon2 << "'s " << attack2 << " is effective against " << pokemon1 << endl;
                }
                out << "  The battle between " << pokemon1 << " and " << pokemon2 << " is a tie." << endl;
            }
            // pokemon1 wins
            if ((damageAToB - damageBToA) > 0) {
                if (effectivities[moves[attack1]].count(pokemon[pokemon2]) == 1) {
                    out << "  " << pokemon1 << "'s " << attack1 << " is super effective against " << pokemon2 << endl;
                }
                else if (ineffectivities[moves[attack1]].count(pokemon[pokemon2]) == 1) {
                    out << "  " << pokemon1 << "'s " << attack1 << " is ineffective against " << pokemon2 << endl;
                }
                else if (effectivities[moves[attack1]].count(pokemon[pokemon2]) == 0 && ineffectivities[moves[attack1]].count(pokemon[pokemon2]) == 0) {
                    out << "  " << pokemon1 << "'s " << attack1 << " is effective against " << pokemon2 << endl;
                }
                if (effectivities[moves[attack2]].count(pokemon[pokemon1]) == 1) {
                    out << "  " << pokemon2 << "'s " << attack2 << " is super effective against " << pokemon1 << endl;
                }
                else if (ineffectivities[moves[attack2]].count(pokemon[pokemon1]) == 1) {
                    out << "  " << pokemon2 << "'s " << attack2 << " is ineffective against " << pokemon1 << endl;
                }
                else if (effectivities[moves[attack2]].count(pokemon[pokemon1]) == 0 && ineffectivities[moves[attack2]].count(pokemon[pokemon1]) == 0) {
                    out << "  " << pokemon2 << "'s " << attack2 << " is effective against " << pokemon1 << endl;
                }
                out << "  In the battle between " << pokemon1 << " and " << pokemon2 << ", " << pokemon1 << " wins!" << endl;
            }
            // pokemon2 wins
            if ((damageAToB - damageBToA) < 0) {
                if (effectivities[moves[attack1]].count(pokemon[pokemon2]) == 1) {
                    out << "  " << pokemon1 << "'s " << attack1 << " is super effective against " << pokemon2 << endl;
                }
                else if (ineffectivities[moves[attack1]].count(pokemon[pokemon2]) == 1) {
                    out << "  " << pokemon1 << "'s " << attack1 << " is ineffective against " << pokemon2 << endl;

                }
                else if (effectivities[moves[attack1]].count(pokemon[pokemon2]) == 0 && ineffectivities[moves[attack1]].count(pokemon[pokemon2]) == 0) {
                    out << "  " << pokemon1 << "'s " << attack1 << " is effective against " << pokemon2 << endl;

                }
                if (effectivities[moves[attack2]].count(pokemon[pokemon1]) == 1) {
                    out << "  " << pokemon2 << "'s " << attack2 << " is super effective against " << pokemon1 << endl;

                }
                else if (ineffectivities[moves[attack2]].count(pokemon[pokemon1]) == 1) {
                    out << "  " << pokemon2 << "'s " << attack2 << " is ineffective against " << pokemon1 << endl;

                }
                else if (effectivities[moves[attack2]].count(pokemon[pokemon1]) == 0 && ineffectivities[moves[attack2]].count(pokemon[pokemon1]) == 0) {
                    out << "  " << pokemon2 << "'s " << attack2 << " is effective against " << pokemon1 << endl;

                }
                out << "  In the battle between " << pokemon1 << " and " << pokemon2 << ", " << pokemon2 << " wins!" << endl;
            }
        }
    }

    return 0;
}

