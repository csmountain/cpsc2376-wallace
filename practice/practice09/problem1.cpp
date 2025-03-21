// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#include <iostream>
#include <string>
#include <limits>

int main()
{
    float redPotion{0.0f};  // Amount of red potion in mL
    float bluePotion{0.0f}; // Amount of blue potion in mL
    float *flask{nullptr};  // Pointer to the selected potion

    std::string potionChoice;
    while (true)
    {
        // Ask the user which potion to add liquid to
        std::cout << "Would you like to add liquid to the 'Red' or 'Blue' potion? ('Done' to exit): ";
        std::cin >> potionChoice;

        // Check if the user wants to exit
        if (potionChoice == "Done" || potionChoice == "done" || potionChoice == "d" || potionChoice == "D")
        {
            break;
        }

        // Update the flask pointer to point to the correct potion
        if (potionChoice == "Red" || potionChoice == "red" || potionChoice == "r" || potionChoice == "R") 
        {
            flask = &redPotion;
        }
        else if (potionChoice == "Blue" || potionChoice == "blue" || potionChoice == "b" || potionChoice == "B")
        {
            flask = &bluePotion;
        }
        else
        {
            std::cout << "\nInvalid choice. Please choose 'Red', 'Blue', or 'Done'.\n\n";
            continue;
        }

        // Ask how many milliliters to add
        float amountToAdd{0.0f};
        while (true)
        {
            std::cout << "\nHow many milliliters (mL) would you like to add? ";
            std::string input;
            std::cin >> input;

            try
            {
            size_t pos;
            amountToAdd = std::stof(input, &pos);

            // Ensure the entire input was consumed and the value is non-negative
            if (pos == input.length() && amountToAdd >= 0.0f)
            {
                break; // Valid input, exit the loop
            }
            else
            {
                throw std::invalid_argument("Invalid input");
            }
            }
            catch (const std::exception &)
            {
            std::cout << "\nInvalid input. Please enter a valid non-negative number.\n";
            }
        }

        // Update the potion level using the flask pointer
        if (flask)
        {
            *flask += amountToAdd;
        }

        // Display both potion levels
        std::cout << "\nRed Potion: " << redPotion << " mL\n";
        std::cout << "\nBlue Potion: " << bluePotion << " mL\n\n";
    }

    std::cout << "\nPotion brewing complete. Final levels:\n";
    std::cout << "\nRed Potion: " << redPotion << " mL\n";
    std::cout << "\nBlue Potion: " << bluePotion << " mL\n\n";

    return 0;
}