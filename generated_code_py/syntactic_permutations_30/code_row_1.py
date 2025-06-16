import re, urllib

target = "http://www.example.com"
match = re.match(r'^[a-zA-Z0-9_-]+\.[a-z]{2,3}$', target)
if match:
    redirect("https://www.example.com")
else:
    redirect("/")