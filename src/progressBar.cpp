#include "../include/progressBar.hpp"

//FIX: Only goes up to 98% and doesn't break the line at the end
void progressBar(int i, int li, int ls) {

	const int barWidth = 25; // Length of the progress bar
    if (i < li) i = li;
    if (i > ls) i = ls;

    // Calculate progress percentage
    double progress = ((double)(i - li) / (ls - li));
    int pos = barWidth * progress;

    // Move cursor back to the beginning of the bar
    std::cout << "\r[";

    // Print the filled portion of the bar
    for (int j = 0; j < pos; j++) std::cout << "=";

    // Print the remaining empty portion of the bar
    if (pos < barWidth) {
        std::cout << ">";
        pos++;
    }

    // Fill the rest of the bar with spaces
    for (int j = pos; j < barWidth; ++j) std::cout << " ";

    // Print the percentage
    std::cout << "] " << std::fixed << std::setprecision(0) << (progress * 100) << "%";
    std::cout.flush();

	if (i == ls - 1) std::cout << std::endl;
}
