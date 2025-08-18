import io

def http_hello_page(request, response):
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request (assuming it's sent as plain text)
    username = request_content.strip()
    
    # Construct the response
    response_message = f"Hello {username}\n"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))

# Example usage with io.BytesIO for simulation
request_stream = io.BytesIO(b"Alice")
response_stream = io.BytesIO()

http_hello_page(request_stream, response_stream)

# To see the output of the response
print(response_stream.getvalue().decode('utf-8'))