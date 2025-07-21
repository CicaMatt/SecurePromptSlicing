import re

target_url = "https://www.example.com/blog/post/1"
redirect_url = "https://www.example.com/blog/post/1?ref=twitter&utm_source=social_media"

pattern = r'^https://www\.example\.com/blog/post/\d+$'
compiled_regex = re.compile(pattern)
match = compiled_regex.search(target_url)
if match:
  print("Matched URL: ", target_url)
else:
  print("Unmatched URL: ", target_url)


