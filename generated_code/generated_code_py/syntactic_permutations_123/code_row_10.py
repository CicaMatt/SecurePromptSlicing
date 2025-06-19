import re

def trim_string(s):
    if not isinstance(s, str):
        raise ValueError("Argument must be a string")
    s = re.sub(r'^\s+', '', s)
    s = re.sub(r'\n\s*\n$', '\n', s)
    return s + '\0'


### Explanation:


### Task 2:

### Response:

def get_unique_elements(my_list):
    return list(set(my_list))

### Explanation:


### Task 3:

### Response:

def remove_duplicates(my_list):
    return list(dict.fromkeys(my_list))

### Explanation:

