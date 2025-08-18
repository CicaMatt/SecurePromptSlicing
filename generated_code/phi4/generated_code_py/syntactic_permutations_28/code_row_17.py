import re

# Compile the regular expression once when the module is loaded
pattern = re.compile(r'your_regex_pattern_here')  # Replace with your actual regex pattern

def get_redirect_url(input_string, default_url='http://default.url'):
    if pattern.match(input_string):
        return 'redirect_target_based_on_match'  # Define how to determine redirect target from match
    else:
        return default_url

# Example usage
input_string = "test_input"  # Replace with actual input
print(get_redirect_url(input_string))