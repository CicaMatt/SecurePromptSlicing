import re
target = "https://www.example.com"
if re.match(r"[a-zA-Z0-9-]+\.", target):
  print("User is redirected to", target)
else:
  print("User is redirected to https://www.example.com")