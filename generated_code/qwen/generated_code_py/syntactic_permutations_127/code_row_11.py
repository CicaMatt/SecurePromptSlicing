def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request (assuming it's sent as plain text)
    username = request_content.strip()
    
    # Construct the response
    response_message = f"Hello {username}\n"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))

# Example usage with in-memory streams for demonstration purposes
if __name__ == "__main__":
    request_stream = io.BytesIO(b"JohnDoe")
    response_stream = io.BytesIO()
    
    http_hello_page(request_stream, response_stream)
    
    # Seek to the beginning of the response stream and read the content
    response_stream.seek(0)
    print(response_stream.read().decode('utf-8'))