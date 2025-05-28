def http_hello_page(request, response):
    # read in username from the request
    username = request.read()

    # construct a personalized greeting message
    greeting = f"Hello, {username}!"

    # write the greeting to the response
    response.write(greeting)

    # send the response back to the client
    return response