def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_data = request.read().decode('utf-8')
    
    # Assuming the username is sent as plain text in the request body
    username = request_data.strip()
    
    # Construct the response
    response_content = f"Hello {username}"
    
    # Write the response to the response file stream
    response.write(response_content.encode('utf-8'))
    response.flush()

# Example usage with io.BytesIO for simulation purposes
request_stream = io.BytesIO(b"Alice")
response_stream = io.BytesIO()
http_hello_page(request_stream, response_stream)
print(response_stream.getvalue().decode('utf-8'))  # Output: Hello Alice