import re
regex = r"\d"  # Match any digit character from 0 to 9.
test_str = "123"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\w"  # Match any word character from a-z, A-Z, 0-9, _.
test_str = "a"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\W"  # Match any non-word character.
test_str = "#"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\s"  # Match a single white space character (spaces, tabs and line breaks).
test_str = " "
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\S"  # Match a single non-white space character.
test_str = "a"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\d+"  # Match one or more digit characters from 0 to 9.
test_str = "123"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\w+"  # Match one or more word characters from a-z, A-Z, 0-9, _.
test_str = "a"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\W+"  # Match one or more non-word characters.
test_str = "#"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\s+"  # Match one or more white space characters (spaces, tabs and line breaks).
test_str = " "
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\S+"  # Match one or more non-white space characters.
test_str = "a"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\d*"  # Match zero or more digit characters from 0 to 9.
test_str = "123"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\w*"  # Match zero or more word characters from a-z, A-Z, 0-9, _.
test_str = "a"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\W*"  # Match zero or more non-word characters.
test_str = "#"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\s*"  # Match zero or more white space characters (spaces, tabs and line breaks).
test_str = " "
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"\S*"  # Match zero or more non-white space characters.
test_str = "a"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^abc$"  # Matches the string "abc".
test_str = "abc"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^abc"  # Matches any string that starts with "abc".
test_str = "abc"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^abc"  # Matches any string that starts with "abc".
test_str = "abcd"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"abc$"  # Matches any string that ends with "abc".
test_str = "abc"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"abc$"  # Matches any string that ends with "abc".
test_str = "dabcd"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^$"  # Matches an empty string.
test_str = ""
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a(bc)$"  # Capture group.
test_str = "abc"
match = re.search(regex, test_str)
if match:
    print("Match -> {}".format(match.group(1)))
else:
    print("No match")

import re
regex = r"^a(bc)$"  # Capture group.
test_str = "abc"
match = re.search(regex, test_str)
if match:
    print("Match -> {}".format(match.group(0)))
else:
    print("No match")

import re
regex = r"^a(bc)$"  # Capture group.
test_str = "abc"
match = re.search(regex, test_str)
if match:
    print("Match -> {}".format(match.group()))
else:
    print("No match")

import re
regex = r"^a(b)c$"  # Capture group.
test_str = "abc"
match = re.search(regex, test_str)
if match:
    print("Match -> {}".format(match.group(1)))
else:
    print("No match")

import re
regex = r"^a(b)c$"  # Capture group.
test_str = "abc"
match = re.search(regex, test_str)
if match:
    print("Match -> {}".format(match.group(1, 2)))
else:
    print("No match")

import re
regex = r"^a(b)c$"  # Capture group.
test_str = "abc"
match = re.search(regex, test_str)
if match:
    print("Match -> {}".format(match.group(0)))
else:
    print("No match")

import re
regex = r"^a(b)c$"  # Capture group.
test_str = "abc"
match = re.search(regex, test_str)
if match:
    print("Match -> {}".format(match.group()))
else:
    print("No match")

import re
regex = r"^a[bc]d$"  # Character class.
test_str = "abd"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bc]d$"  # Character class.
test_str = "acd"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[b-d]e$"  # Character class.
test_str = "ace"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[b-d]e$"  # Character class.
test_str = "abe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[b-d]e$"  # Character class.
test_str = "ade"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[^bc]d$"  # Negated character class.
test_str = "aed"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[^bc]d$"  # Negated character class.
test_str = "abd"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[^\w\s]d$"  # Negated character class.
test_str = "a-d"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[^\w\s]d$"  # Negated character class.
test_str = "ad"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]e$"  # Character class with multiple characters.
test_str = "ace"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]e$"  # Character class with multiple characters.
test_str = "ade"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]e$"  # Character class with multiple characters.
test_str = "abe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]e$"  # Character class with multiple characters.
test_str = "aee"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]+e$"  # One or more characters in the character class.
test_str = "abbbbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]+e$"  # One or more characters in the character class.
test_str = "abbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]+e$"  # One or more characters in the character class.
test_str = "adde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]+e$"  # One or more characters in the character class.
test_str = "acde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]+e$"  # One or more characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]+e$"  # One or more characters in the character class.
test_str = "abe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]+e$"  # One or more characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]+e$"  # One or more characters in the character class.
test_str = "abbbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]*e$"  # Zero or more characters in the character class.
test_str = "ae"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]*e$"  # Zero or more characters in the character class.
test_str = "abe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]*e$"  # Zero or more characters in the character class.
test_str = "abbbbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]*e$"  # Zero or more characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]*e$"  # Zero or more characters in the character class.
test_str = "abcd"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]*e$"  # Zero or more characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]?e$"  # Zero or one characters in the character class.
test_str = "ae"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]?e$"  # Zero or one characters in the character class.
test_str = "abe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]?e$"  # Zero or one characters in the character class.
test_str = "abbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]?e$"  # Zero or one characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{3}e$"  # Exactly three characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{3}e$"  # Exactly three characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{3}e$"  # Exactly three characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{3}e$"  # Exactly three characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{3}e$"  # Exactly three characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{2}e$"  # Exactly two characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{2}e$"  # Exactly two characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{2}e$"  # Exactly two characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{2}e$"  # Exactly two characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{2}e$"  # Exactly two characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1}e$"  # Exactly one character in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1}e$"  # Exactly one character in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1}e$"  # Exactly one character in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1}e$"  # Exactly one character in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1}e$"  # Exactly one character in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0}e$"  # Exactly zero characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0}e$"  # Exactly zero characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0}e$"  # Exactly zero characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0}e$"  # Exactly zero characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0}e$"  # Exactly zero characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,3}e$"  # One to three characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,3}e$"  # One to three characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,3}e$"  # One to three characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,3}e$"  # One to three characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,3}e$"  # One to three characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,2}e$"  # One to two characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,2}e$"  # One to two characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,2}e$"  # One to two characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,2}e$"  # One to two characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,2}e$"  # One to two characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,}e$"  # One or more characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,}e$"  # One or more characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,}e$"  # One or more characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,}e$"  # One or more characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,}e$"  # One or more characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,2}e$"  # Zero to two characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,2}e$"  # Zero to two characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,2}e$"  # Zero to two characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,2}e$"  # Zero to two characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,2}e$"  # Zero to two characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,1}e$"  # Zero to one characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,1}e$"  # Zero to one characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,1}e$"  # Zero to one characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,1}e$"  # Zero to one characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,1}e$"  # Zero to one characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,}e$"  # Zero or more characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,}e$"  # Zero or more characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,}e$"  # Zero or more characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,}e$"  # Zero or more characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,}e$"  # Zero or more characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,3}$"  # One to three characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,3}$"  # One to three characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,3}$"  # One to three characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,2}$"  # One to two characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,2}$"  # One to two characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,2}$"  # One to two characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,}$"  # One or more characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,}$"  # One or more characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{1,}$"  # One or more characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,2}$"  # Zero to two characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,2}$"  # Zero to two characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,2}$"  # Zero to two characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,1}$"  # Zero to one characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,1}$"  # Zero to one characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,1}$"  # Zero to one characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,}$"  # Zero or more characters in the character class.
test_str = "abbbbe"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,}$"  # Zero or more characters in the character class.
test_str = "abcde"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")

import re
regex = r"^a[bcd]{0,}$"  # Zero or more characters in the character class.
test_str = "abce"
if re.search(regex, test_str):
    print("Match")
else:
    print("No match")