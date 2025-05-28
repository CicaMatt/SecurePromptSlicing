import re\n
target = request.args.get("target")\n
regex = r"^[a-zA-Z0-9-]+\.[a-zA-Z]{2,}$"\n
if(re.match(target, regex)): redirect(target)\n
else: redirect("/")