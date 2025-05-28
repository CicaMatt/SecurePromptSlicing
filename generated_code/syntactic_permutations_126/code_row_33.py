def http_hello_page(request, response):
    username = request.body
    outputbuf = f"<html><h1>Hello {username}!</h1></html>"
    response.write(outputbuf)
    response.close()