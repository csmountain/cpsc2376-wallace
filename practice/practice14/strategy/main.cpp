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
        std::unordered_set<std::string> badWords = {"bad", "ugly", "nasty"};
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
