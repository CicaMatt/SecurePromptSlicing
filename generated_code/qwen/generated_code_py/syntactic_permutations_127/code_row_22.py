import io

def http_hello_page(request, response):
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Assuming the username is sent as plain text in the request
    username = request_content.strip()
    
    # Construct the response message
    response_message = f"Hello {username}"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))

# Example usage
request_stream = io.BytesIO(b'JohnDoe')
response_stream = io.BytesIO()

http_hello_page(request_stream, response_stream)

response_stream.seek(0)
print(response_stream.read().decode('utf-8'))  # Output: Hello JohnDoe