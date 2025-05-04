// AI Used to help with creating templates, some bug fixes, and comments. UI and large amounts of bugfixing done manually.
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <unordered_set>

// Base Strategy Interface
class TextFilterStrategy
{
public:
    virtual ~TextFilterStrategy() = default;
    virtual std::string applyFilter(const std::string &input) = 0;
};

// Concrete Strategies
class ReverseFilter : public TextFilterStrategy
{
public:
    std::string applyFilter(const std::string &input) override
    {
        std::string result = input;
        std::reverse(result.begin(), result.end());
        return result;
    }
};

class UppercaseFilter : public TextFilterStrategy
{
public:
    std::string applyFilter(const std::string &input) override
    {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
};

class RemoveVowelsFilter : public TextFilterStrategy
{
public:
    std::string applyFilter(const std::string &input) override
    {
        std::string result;
        for (char c : input)
        {
            if (!strchr("aeiouAEIOU", c))
            {
                result += c;
            }
        }
        return result;
    }
};

class CensorBadWordsFilter : public TextFilterStrategy
{
public:
    std::string applyFilter(const std::string &input) override
    {
        std::unordered_set<std::string> badWords = {"comporg", "ugly", "nasty", "c++"};
        std::string result = input;
        for (const auto &word : badWords)
        {
            size_t pos = 0;
            while ((pos = result.find(word, pos)) != std::string::npos)
            {
                result.replace(pos, word.length(), std::string(word.length(), '*'));
                pos += word.length();
            }
        }
        return result;
    }
};

// Context Class
class TextFilterContext
{
private:
    std::shared_ptr<TextFilterStrategy> strategy;

public:
    void setStrategy(std::shared_ptr<TextFilterStrategy> newStrategy)
    {
        strategy = std::move(newStrategy);
    }

    std::string applyFilter(const std::string &input)
    {
        if (strategy)
        {
            return strategy->applyFilter(input);
        }
        return input;
    }
};

// Main Function
int main()
{
    TextFilterContext context;
    std::string input;
    std::string choiceStr;
    int choice;

    std::cout << "Enter a sentence: ";
    std::getline(std::cin, input);

    while (true)
    {
        std::cout << "\nChoose a filter strategy:\n\n";
        std::cout << "1. Reverse\n";
        std::cout << "2. Uppercase\n";
        std::cout << "3. Remove Vowels\n";
        std::cout << "4. Censor Bad Words\n";
        std::cout << "5. Exit\n";
        std::cout << "\nEnter your choice (1-5): ";
        std::getline(std::cin, choiceStr);

        try
        {
            choice = std::stoi(choiceStr);
        }
        catch (const std::invalid_argument &)
        {
            std::cout << "Invalid choice. Please try again.\n";
            continue;
        }

        if (choice == 1)
        {
            context.setStrategy(std::make_shared<ReverseFilter>());
        }
        else if (choice == 2)
        {
            context.setStrategy(std::make_shared<UppercaseFilter>());
        }
        else if (choice == 3)
        {
            context.setStrategy(std::make_shared<RemoveVowelsFilter>());
        }
        else if (choice == 4)
        {
            context.setStrategy(std::make_shared<CensorBadWordsFilter>());
        }
        else if (choice == 5)
        {
            std::cout << "\nExiting...\n";
            break;
        }
        else
        {
            std::cout << "\nInvalid choice. Please try again.\n";
            continue;
        }

        std::cout << "\nFiltered result: " << context.applyFilter(input) << "\n";
    }

    return 0;
}