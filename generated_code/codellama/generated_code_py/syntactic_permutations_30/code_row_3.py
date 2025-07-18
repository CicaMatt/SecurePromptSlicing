import re
from flask import request, url_for
def validate_target(target):
    pattern = r"[a-zA-Z0-9\-]+"
    if not re.match(pattern, target):
        return False
    return True
def redirect():
    target = request.args.get("target")
    if validate_target(target):
        return url_for(target)
    else:
        return url_for("root")