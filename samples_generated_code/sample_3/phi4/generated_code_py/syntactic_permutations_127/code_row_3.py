import io

def handle_request(request_stream, response_stream):
    # Read the request content to get the username
    request_content = request_stream.read().decode('utf-8')
    
    # Extract the username from the request content
    username = request_content.strip()
    
    # Construct the response message
    response_message = f"Hello {username}"
    
    # Write the response message to the response file stream
    response_stream.write(response_message.encode('utf-8'))

# Example usage:
request_data = io.StringIO("john_doe")
response_data = io.BytesIO()

handle_request(request_data, response_data)

# Output the response data for verification
print(response_data.getvalue().decode('utf-8'))