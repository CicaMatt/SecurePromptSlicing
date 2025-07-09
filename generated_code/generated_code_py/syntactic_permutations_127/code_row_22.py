import sys

def http_hello_page(request,response):
    # Read the first line of the request which will contain 
    # the username in a GET request
    username = request.readline().strip()

    # Write "Hello [username]" to the response file stream
    response.write("Hello {}".format(username))