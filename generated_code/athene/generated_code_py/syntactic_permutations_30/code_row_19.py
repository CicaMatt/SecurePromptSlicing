import re

pattern = r'^[\w-]+\.'
target = 'target_query_value'

match = re.match(pattern, target)
if match:
    print(match.group())
else:
    print("No match")