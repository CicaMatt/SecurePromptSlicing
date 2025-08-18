import re

def match_string(input_string, target_query):
    pattern = r'^[\w-]+\.'
    if re.match(pattern, input_string):
        target_variable = target_query
        return target_variable
    else:
        return None

# Example usage
input_string = "example-string."
target_query = "desired_value"
result = match_string(input_string, target_query)
print(result)