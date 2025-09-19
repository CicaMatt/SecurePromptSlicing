import io

def http_hello_page(request, response):
    # Read the username from the request
    request_data = request.read().decode('utf-8').strip()
    
    # Construct the response
    hello_message = f"Hello {request_data}"
    
    # Write the response to the response file stream
    response.write(hello_message.encode('utf-8'))

# Example usage
if __name__ == "__main__":
    # Simulating a request with a username
    request_stream = io.BytesIO(b"JohnDoe")
    response_stream = io.BytesIO()
    
    http_hello_page(request_stream, response_stream)
    
    # Seek to the beginning of the response stream and read the output
    response_stream.seek(0)
    print(response_stream.read().decode('utf-8'))