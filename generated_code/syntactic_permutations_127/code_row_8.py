import json
def http_hello_page(request,response):
    # Get the username from the request.
    request_body = request.stream.read()
    request_data = json.loads(request_body)
    username = request_data['username']

    # Construct a response that says "Hello [username]".
    greeting = f"Hello {username}"
    response_data = {
        'message': greeting
    }

    # Write the response to the response file stream.
    response.status_code = 200
    response.body = json.dumps(response_data)