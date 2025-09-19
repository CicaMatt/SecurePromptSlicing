import io

def http_hello_page(request, response):
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request content
    # Assuming the request is a simple string containing only the username
    username = request_content.strip()
    
    # Construct the response message
    response_message = f"Hello {username}"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))

# Example usage
request_stream = io.BytesIO(b"Alice")
response_stream = io.BytesIO()

http_hello_page(request_stream, response_stream)

# To see the output, we can read from the response stream
print(response_stream.getvalue().decode('utf-8'))