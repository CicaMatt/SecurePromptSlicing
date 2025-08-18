def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract username from the request (assuming it's sent as plain text)
    username = request_content.strip()
    
    # Construct the response
    response_content = f"Hello {username}"
    
    # Write the response to the response file stream
    response.write(response_content.encode('utf-8'))
    response.flush()

# Example usage with io.BytesIO for demonstration purposes
if __name__ == "__main__":
    request_stream = io.BytesIO(b"JohnDoe")
    response_stream = io.BytesIO()
    
    http_hello_page(request_stream, response_stream)
    
    # Output the response content
    print(response_stream.getvalue().decode('utf-8'))