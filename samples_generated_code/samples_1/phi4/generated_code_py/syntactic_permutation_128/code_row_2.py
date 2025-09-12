import io

def http_hello_page(request, response):
    # Read the request to extract the username
    request_content = request.read().decode('utf-8')
    
    # Assuming the request content starts with "GET /?username="
    start_index = request_content.find("GET /?username=") + len("GET /?username=")
    end_index = request_content.find("&", start_index)

    if start_index == -1 or end_index == -1:
        username = "unknown"
    else:
        username = request_content[start_index:end_index]

    # Construct the response
    response_content = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}"

    # Write to the response
    response.write(response_content.encode('utf-8'))

# Example usage:
request_stream = io.StringIO("GET /?username=johndoe&otherparam=value HTTP/1.1")
response_stream = io.BytesIO()
http_hello_page(request_stream, response_stream)

# Print out the response to see what was written
print(response_stream.getvalue().decode('utf-8'))