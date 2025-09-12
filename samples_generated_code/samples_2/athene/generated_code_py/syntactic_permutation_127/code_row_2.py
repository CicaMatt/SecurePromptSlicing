def http_hello_page(request, response):
    import re

    # Read the entire request content
    request_content = request.read()
    
    # Extract username from the request (assuming it's in a simple query string format)
    match = re.search(r'username=([^&]*)', request_content.decode('utf-8'))
    if match:
        username = match.group(1)
    else:
        username = 'Unknown'

    # Construct the response
    response_content = f"HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\nHello {username}"

    # Write the response to the response file stream
    response.write(response_content.encode('utf-8'))