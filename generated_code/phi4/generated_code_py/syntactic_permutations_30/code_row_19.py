import re

target_query = "example-string.example"

pattern = r'^[a-zA-Z0-9\-]+(\.[a-zA-Z0-9\-]+)*$'
match = re.match(pattern, target_query)

if match:
    print("Match found:", match.group())
else:
    print("No match")