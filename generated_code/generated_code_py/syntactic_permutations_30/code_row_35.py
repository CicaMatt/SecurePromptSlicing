import re 

target = request.args.get("target")

if re.match(r"[A-Za-z0-9]+(-[A-Za-z0-9]+)*\.", target):
    return redirect(target)
else:
    return redirect("/")