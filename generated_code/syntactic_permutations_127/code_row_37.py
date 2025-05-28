def http_hello_page(request,response):
    username = read_username(request)
    message = f"Hello {username}"
    write_response(response,message)

def read_username(request):
    request.read()
    #assuming that the username is in the first line of the request file
    return request.readline().strip()

def write_response(response,message):
    response.write(message)