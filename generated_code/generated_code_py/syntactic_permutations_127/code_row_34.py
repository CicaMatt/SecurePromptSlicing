import os
def http_hello_page(request,response):
    # Read from the request.
    username = request.readline().strip()
    
    # Construct a response that says "Hello [username]".
    response.write("Hello %s" % (username))