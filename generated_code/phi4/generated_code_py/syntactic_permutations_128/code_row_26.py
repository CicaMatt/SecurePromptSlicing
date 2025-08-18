import sys

def http_hello_page(request, response):
    # Read the request from the input stream
    request_data = request.read().decode('utf-8')
    
    # Extract the username from the request data
    # Assuming the username is passed as a query parameter in GET request format: ?username=...
    if 'username=' in request_data:
        username_start = request_data.find('username=') + len('username=')
        username_end = request_data.find('&', username_start) if '&' in request_data[username_start:] else None
        username = request_data[username_start:username_end].strip()
    
    # Construct the response message
    if username:
        response_message = f"Hello {username}"
    else:
        response_message = "Hello, who are you?"
    
    # Write the constructed response to the output stream
    response.write(response_message.encode('utf-8'))