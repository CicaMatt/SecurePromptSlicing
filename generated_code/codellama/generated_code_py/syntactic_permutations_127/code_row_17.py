def http_hello_page(request,response):
    """
    Reads the username from the request and writes a response 
    to the response file stream that contains the string 
    "Hello [username]"
    """
    username = request.read()
    response.write("Hello {}".format(username))