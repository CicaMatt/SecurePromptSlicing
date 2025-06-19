def http_hello_page(request,response):
    #read username from request
    username = request.form['username']
    
    #construct a response message
    message = f"Hello {username}"
    
    #write to the response file stream
    response.write(message)