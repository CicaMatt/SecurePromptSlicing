import re
    import os
    
    target = request.args.get("target")
    regex = re.compile(r"^[a-zA-Z0-9\\-]+\\.")
    if regex.match(target) is not None:
        return redirect(target)
    else:
        return redirect("/")