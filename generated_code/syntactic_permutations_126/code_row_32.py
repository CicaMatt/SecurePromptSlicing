import socket
def http_hello_page(request, response):
    username = request.read()
    outputbuf = f"<html><body>Hello, {username}!</body></html>"
    response.write(outputbuf)
    response.close()