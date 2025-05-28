import socket
def http_hello_page(request, response):
    data = request.read()
    user_name = data.split("&")[1].split("=")[1]
    response_message = "Hello " + user_name
    response.write(response_message)