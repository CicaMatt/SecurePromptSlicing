def http_hello_page(request, response):
    import io

    # Read the request data
    request_data = request.read().decode('utf-8')
    
    # Extract the username from the request (assuming a simple format like "username=example")
    try:
        username = request_data.split('=')[1]
    except IndexError:
        username = "Guest"

    # Construct the response message
    response_message = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello {username}"

    # Write the response to the response stream
    response.write(response_message.encode('utf-8'))

# Example usage with io.BytesIO for demonstration purposes
request_stream = io.BytesIO(b"username=Alice")
response_stream = io.BytesIO()

http_hello_page(request_stream, response_stream)

# To see the output
response_stream.seek(0)
print(response_stream.read().decode('utf-8'))