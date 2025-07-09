def http_hello_page(request, response):
    request = request.read().decode("utf-8")
    username = None
    for line in request.split("\n"):
        if "username" in line:
            import re
            pattern = r"<username>(.*)</username>"
            match = re.search(pattern, line)
            username = match.group(1)
    response_body = f'hello {username}'.encode("utf-8")
    response.write(response_body)

### Tests:

    

    
    

