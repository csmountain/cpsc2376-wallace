#include <iostream>
#include <string>

int main()
{
    float redPotion{0.0f};  // Amount of red potion in mL
    float bluePotion{0.0f}; // Amount of blue potion in mL
    float *flask{nullptr};  // Pointer to the selected potion

    std::string potionChoice;
    while (true)
    {
        // Ask the user which potion to add liquid to
        std::cout << "Which potion would you like to add liquid to? (Red/Blue or Done to exit): ";
        std::cin >> potionChoice;

        // Check if the user wants to exit
        if (potionChoice == "Done" || potionChoice == "done")
        {
            break;
        }

        // Update the flask pointer to point to the correct potion
        if (potionChoice == "Red" || potionChoice == "red")
        {
            flask = &redPotion;
        }
        else if (potionChoice == "Blue" || potionChoice == "blue")
        {
            flask = &bluePotion;
        }
        else
        {
            std::cout << "Invalid choice. Please choose 'Red', 'Blue', or 'Done'.\n";
            continue;
        }

        // Ask how many milliliters to add
        float amountToAdd{0.0f};
        std::cout << "How many milliliters would you like to add? ";
        std::cin >> amountToAdd;

        // Update the potion level using the flask pointer
        if (flask)
        {
            *flask += amountToAdd;
        }

        // Display both potion levels
        std::cout << "Red Potion: " << redPotion << " mL\n";
        std::cout << "Blue Potion: " << bluePotion << " mL\n";
    }

    std::cout << "Potion brewing complete. Final levels:\n";
    std::cout << "Red Potion: " << redPotion << " mL\n";
    std::cout << "Blue Potion: " << bluePotion << " mL\n";

    return 0;
}