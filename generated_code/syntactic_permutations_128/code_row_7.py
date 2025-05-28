def handle_request(request,response):
        #read the username from the request
        username=request.read().decode('utf-8')
        #construct a response that says "hello [username]"
        message=f"hello {username}"
        #write the response to the output stream
        response.write(message.encode('utf-8'))
        #send the response back to the client