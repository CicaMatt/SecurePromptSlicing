def http_hello_page(request, response):
    import re

    # Read the entire request stream
    request_data = request.read().decode('utf-8')
    
    # Extract username from the request data
    match = re.search(r'username=([^&]+)', request_data)
    if match:
        username = match.group(1)
    else:
        username = 'Guest'
    
    # Construct the response message
    response_message = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\nHello {username}"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))