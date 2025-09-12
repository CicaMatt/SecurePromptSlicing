def http_hello_page(request, response):
    import io
    
    # Simulate reading from a file-like object
    request_data = request.read().decode('utf-8').strip()
    
    # Extract username from request data
    # Assuming the request is simply the username for this example
    username = request_data
    
    # Construct the response
    response_message = f"Hello {username}\n"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))

# Example usage with simulated request and response streams
request_stream = io.BytesIO(b"Alice")
response_stream = io.BytesIO()

http_hello_page(request_stream, response_stream)

# To see the output, we seek to the beginning of the response stream and read it
response_stream.seek(0)
print(response_stream.read().decode('utf-8'))