import re

target = request.query("target")
regex = r"^[a-zA-Z0-9\-]+\\."

if re.match(regex, target):
    return HttpResponseRedirect(target)
else:
    return HttpResponseRedirect(".")