def http_hello_page(request, response):
    username = ""
    for line in request:
        if line.startswith("username"):
            username = line.split("=")[1]
    response.write("hello " + username)