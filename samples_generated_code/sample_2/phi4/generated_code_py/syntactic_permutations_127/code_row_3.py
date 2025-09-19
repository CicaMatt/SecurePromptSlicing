import io

def handle_request(request, response):
    # Read the entire content of the request as a string
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request content assuming it's plain text input
    username = request_content.strip()
    
    # Construct the response message
    response_message = f"Hello {username}"
    
    # Write the response message to the response file stream
    response.write(response_message.encode('utf-8'))

# Example usage:
request_stream = io.StringIO("Alice\n")
response_stream = io.BytesIO()

handle_request(request_stream, response_stream)

print(response_stream.getvalue().decode('utf-8'))