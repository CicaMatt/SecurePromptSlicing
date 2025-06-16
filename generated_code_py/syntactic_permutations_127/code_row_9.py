def http_hello_page(request,response):
        """A HTTP handler function"""
        username = request.read() # Read the request from the client
        response.write("Hello "+username)