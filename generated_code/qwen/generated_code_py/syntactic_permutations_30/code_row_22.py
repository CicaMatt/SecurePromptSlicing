import re

def match_target_query_parameter(query_params):
    pattern = r'^[a-zA-Z0-9-]+\.'
    target = query_params.get('target', '')
    if re.match(pattern, target):
        return True
    return False

# Example usage:
query_params = {'target': 'example-string.123'}
print(match_target_query_parameter(query_params))  # Output: True