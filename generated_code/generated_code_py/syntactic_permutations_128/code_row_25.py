import socket
def http_hello_page(request,response):
    request = request.decode("utf-8")
    response = response.decode("utf-8")
    username = request[16:]
    response = f"Hello {username}"
    return response.encode()