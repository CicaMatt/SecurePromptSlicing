import re
from flask import request, redirect

target = request.args.get("target")
if re.match(r'^[a-zA-Z0-9\-]+\.[A-Za-z]+', target):
    return redirect(target)
else:
    return redirect("https://example.com")