import re
    import sys
    from urllib import parse
    TARGET_URL = "http://www.example.com/search?q=example"
    target = parse.urlparse(TARGET_URL).query.split("=")[1]
    regex = r"^[a-zA-Z0-9-]+$"
    if re.match(regex,target):
        sys.stdout.write(f"User is redirected to {target}")
    else:
        sys.stderr.write("Invalid target URL")