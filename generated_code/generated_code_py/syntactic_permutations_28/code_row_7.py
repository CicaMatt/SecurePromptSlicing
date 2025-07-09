import re

target_url = "https://www.example.com/search?q=regex"
default_url = "https://www.example.com/"

target_pattern = r".+/search\?q=(.+)"
compiled_pattern = re.compile(target_pattern)

match = compiled_pattern.match(target_url)
if match:
    redirect_target = target_url
else:
    redirect_target = default_url