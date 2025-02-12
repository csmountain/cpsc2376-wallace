Formatting courtesy of Carter Wallace. AI used to find out how to create headers and highlighted points. Problems found by me but rewritten by AI For formatting and clarity.

# Fixes

## Bug 1: Off-by-one error in sumRange

- Issue: `sumRange` should include the end value.
- Problems Caused: The function does not correctly sum the range including the `end` value.
- Fix: Change the loop condition from `i < end` to `i <= end`.

## Bug 2: Incorrect loop condition in containsNegative

- Issue: `containsNegative` should iterate up to `numbers.size() - 1`.
- Problems Caused: Potential out-of-bounds access leading to undefined behavior.
- Fix: Change the loop condition from `i <= numbers.size()` to `i < numbers.size()`.

## Bug 3: Incorrect condition check in containsNegative

- Issue: The condition should check for negative numbers.
- Problems Caused: Incorrectly identifies the presence of negative numbers.
- Fix: Change the condition from `numbers[i] > 0` to `numbers[i] < 0`.

## Bug 4: Incorrect loop condition in findMax

- Issue: `findMax` should iterate up to `numbers.size() - 1`.
- Problems Caused: Potential out-of-bounds access leading to undefined behavior.
- Fix: Change the loop condition from `i <= numbers.size()` to `i < numbers.size()`.

## Bug 5: Incorrect comparison in findMax

- Issue: The comparison should correctly identify the maximum value.
- Problems Caused: Incorrectly identifies the maximum value.
- Fix: Change the comparison from `numbers[i] >= maxVal` to `numbers[i] > maxVal`.

## Bug 6: Incorrect handling of empty vector in findMax

- Issue: Accessing out-of-bounds element when the list is empty.
- Problems Caused: Incorrect handling of empty vectors.
- Fix: Throw an exception for an empty vector.