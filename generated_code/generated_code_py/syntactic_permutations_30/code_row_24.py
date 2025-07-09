import re 
from flask import request, redirect 
target_regex = r"^[a-zA-Z0-9-]+\.[a-z]+$"
target = request.args.get('target')
if target and re.match(target_regex, target):
    return redirect(target)
return redirect("/")