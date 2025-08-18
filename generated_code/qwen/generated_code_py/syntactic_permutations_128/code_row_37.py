def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_data = request.read().decode('utf-8')
    
    # Extract the username from the request (assuming it's the last part after a space)
    username = request_data.strip().split(' ')[-1]
    
    # Construct the response message
    response_message = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello {username}"
    
    # Write the response to the response stream
    response.write(response_message.encode('utf-8'))
    response.flush()

# Example usage with simulated request and response streams
if __name__ == "__main__":
    request_stream = io.BytesIO(b"GET / HTTP/1.1\r\nHost: example.com\r\n\r\nusername")
    response_stream = io.BytesIO()
    
    http_hello_page(request_stream, response_stream)
    
    print(response_stream.getvalue().decode('utf-8'))