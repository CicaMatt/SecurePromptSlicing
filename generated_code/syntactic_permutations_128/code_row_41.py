def http_hello_page(request, response):
    request = str(request).split()
    username = request[1].split("=")[1]
    message = "hello " + username
    response.write(message)