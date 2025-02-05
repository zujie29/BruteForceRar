#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include <cstdlib>

// Fonction pour calculer le nombre total de combinaisons possibles
unsigned long long count_combinations(const std::string &charset, int min_length, int max_length) {
    unsigned long long total = 0;
    for (int length = min_length; length <= max_length; ++length) {
        total += std::pow(charset.size(), length);
    }
    return total;
}

// Fonction récursive pour générer et tester des combinaisons de mots de passe
bool generate_combinations(std::ofstream &output_file, const std::string &charset, const std::string &current,
                           int max_length, const std::string &rar_file, unsigned long long &tested_count, 
                           unsigned long long total_combinations) {
    if (current.size() == max_length) {
        std::string command = "unrar t -p" + current + " " + rar_file + " > /dev/null 2>&1";
        int result = system(command.c_str());

        // Afficher la progression
        ++tested_count;
        int progress = static_cast<int>((tested_count * 100) / total_combinations);
        std::cout << "\rCrackage en progression: " << progress << "%    " << std::flush;

        if (result == 0) {  // Si le mot de passe est trouvé
            output_file << "Mot de passe trouvé : " << current << std::endl;
            
            // Ouvrir automatiquement le fichier contenant le mot de passe
            std::cout << "\nMot de passe trouvé : " << current << std::endl;
            std::cout << "Ouverture du fichier contenant le mot de passe..." << std::endl;
            output_file.close();
            
            // Lancer l'ouverture du fichier (fonctionne sur la plupart des systèmes UNIX avec la commande `xdg-open`)
            std::string open_command = "xdg-open " + output_file.tellp();
            system(open_command.c_str());

            return true;
        }
        return false;
    }

    for (char c : charset) {
        if (generate_combinations(output_file, charset, current + c, max_length, rar_file, tested_count, total_combinations)) {
            return true;  // Arrête la génération si le mot de passe est trouvé
        }
    }
    return false;
}

// Fonction principale pour l'attaque brute force avec une longueur minimale et maximale
void brute_force_rar(const std::string &output_filename, const std::string &charset, const std::string &rar_file,
                     int min_length, int max_length) {
    std::ofstream output_file(output_filename);
    if (!output_file.is_open()) {
        std::cerr << "Erreur d'ouverture du fichier de sortie." << std::endl;
        return;
    }

    unsigned long long total_combinations = count_combinations(charset, min_length, max_length);
    unsigned long long tested_count = 0;  // Compteur pour suivre le nombre de mots de passe testés

    std::cout << "Démarrage de l'attaque brute force, veuillez patienter...\n";
    std::cout << "Total de combinaisons possibles : " << total_combinations << "\n";

    // Boucle sur chaque longueur de mot souhaitée
    for (int length = min_length; length <= max_length; ++length) {
        if (generate_combinations(output_file, charset, "", length, rar_file, tested_count, total_combinations)) {
            std::cout << "\nMot de passe trouvé et fichier ouvert !" << std::endl;
            return;
        }
    }

    output_file.close();
    std::cout << "\nMot de passe non trouvé dans la plage spécifiée." << std::endl;
}

int main() {
    std::string output_filename;
    std::string charset;
    std::string rar_file;
    int min_length, max_length;
    
    std::cout << "Nom du fichier .rar à déverrouiller (path/kali/...): ";
    std::cin >> rar_file;
    std::cout << "Caractères à utiliser pour les combinaisons (@#*-123ABC...): ";
    std::cin >> charset;
    std::cout << "Longueur minimale des mots de passe : ";
    std::cin >> min_length;
    std::cout << "Longueur maximale des mots de passe : ";
    std::cin >> max_length;
    std::cout << "Fichier pour capturer le mot de passe trouvé : ";
    std::cin >> output_filename;

    if (min_length > max_length) {
        std::cerr << "La longueur minimale doit être inférieure ou égale à la longueur maximale." << std::endl;
        return 1;
    }

    brute_force_rar(output_filename, charset, rar_file, min_length, max_length);

    return 0;
}
