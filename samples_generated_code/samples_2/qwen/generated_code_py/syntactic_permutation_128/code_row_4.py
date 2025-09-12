def http_hello_page(request, response):
    import io

    # Read the request to get the username
    request_data = request.read().decode('utf-8').strip()
    
    # Construct the response
    response_message = f"hello {request_data}"
    
    # Write the response back to the client
    response.write(response_message.encode('utf-8'))
    response.flush()

# Example usage with io.BytesIO for demonstration purposes
if __name__ == "__main__":
    request_stream = io.BytesIO(b"JohnDoe")
    response_stream = io.BytesIO()
    
    http_hello_page(request_stream, response_stream)
    
    # Seek to the beginning of the response stream and read the response
    response_stream.seek(0)
    print(response_stream.read().decode('utf-8'))