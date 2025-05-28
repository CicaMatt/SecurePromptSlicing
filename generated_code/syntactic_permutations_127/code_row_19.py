import http.client as httplib
import os

def hello_page(request, response):
    # Read the username from the request
    username = request.read()

    # Construct a response that says "Hello [username]"
    response_body = f"Hello {username}"

    # Write the response to the response file stream
    response.write(response_body)