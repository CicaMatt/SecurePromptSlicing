import socket
 
def http_hello_page(request,response):
    name = request.read()
    message = f'Hello {name}'
    response.write(message)