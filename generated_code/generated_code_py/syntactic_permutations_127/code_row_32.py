def http_hello_page(request,response):
        #read in request body
        request_body = request.read()
        #get username from request
        username = request_body.split('=')[1]
        #construct response
        response_body = f"Hello {username}"
        #write to response
        response.write(response_body)