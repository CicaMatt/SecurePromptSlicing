import io

def handle_request(request_stream, response_stream):
    # Read the entire content of the request stream as text
    request_content = request_stream.read().decode('utf-8')
    
    # Extract the username from the request content
    # Assuming that the request contains a line with "username: <value>"
    for line in request_content.splitlines():
        if line.startswith("username:"):
            _, username = line.split(":", 1)
            username = username.strip()
            break
    else:
        username = "Unknown"
    
    # Construct the response message
    response_message = f"Hello {username}"
    
    # Write the response to the response file stream
    response_stream.write(response_message.encode('utf-8'))

# Example usage
request_data = io.BytesIO(b'username: JohnDoe\notherdata: irrelevant')
response_data = io.BytesIO()

handle_request(request_data, response_data)

print(response_data.getvalue().decode('utf-8'))  # Output should be "Hello JohnDoe"