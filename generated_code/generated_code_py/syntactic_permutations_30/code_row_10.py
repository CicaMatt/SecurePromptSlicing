import re
from flask import request, redirect, url_for

def validate_target():
    regex = r"^[a-zA-Z0-9]+$"
    target = request.args.get("target")
    if re.match(regex, target):
        return redirect(url_for(target))
    else:
        return redirect(url_for("root"))