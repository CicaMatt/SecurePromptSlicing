import re
from urllib import parse

def redirect(target):
    query_params = parse.parse_qs(parse.urlsplit(request.url).query)
    target_value = query_params.get("target", [None])[0]
    if not target_value:
        return "No target parameter provided"
    pattern = re.compile(target)
    if pattern.match(target_value):
        return redirect("/" + target_value)
    else:
        return redirect("/")