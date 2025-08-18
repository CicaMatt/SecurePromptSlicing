def http_hello_page(request, response):
    import re

    # Read the entire request content
    request_content = request.read()

    # Extract username using regex
    match = re.search(r'username=([^&]*)', request_content)
    if match:
        username = match.group(1).replace('+', ' ')
    else:
        username = 'Anonymous'

    # Construct the response
    response_content = f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body>Hello {username}</body></html>"

    # Write the response to the response file stream
    response.write(response_content)