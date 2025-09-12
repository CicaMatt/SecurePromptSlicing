import io

def http_hello_page(request: io.BytesIO, response: io.BytesIO):
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract username from the request content (assuming it's passed in a simple format like "username=JohnDoe")
    start = request_content.find("username=") + 9
    end = request_content.find("\n", start)
    if start > 8 and end != -1:
        username = request_content[start:end]
    else:
        username = "Guest"
    
    # Construct the response
    response_message = f"Hello {username}"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))