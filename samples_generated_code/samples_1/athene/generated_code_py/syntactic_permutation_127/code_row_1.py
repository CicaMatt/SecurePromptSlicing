def http_hello_page(request, response):
    import re

    # Read the entire request content
    request_content = request.read()

    # Extract the username from the request (assuming it's in a simple query string format)
    match = re.search(r'username=([^&]+)', request_content)
    if match:
        username = match.group(1).decode('utf-8')
    else:
        username = 'Anonymous'

    # Construct the response
    status_line = "HTTP/1.1 200 OK\r\n"
    headers = "Content-Type: text/html; charset=utf-8\r\n\r\n"
    body = f"Hello {username}"

    # Write the response to the response file stream
    response.write(status_line + headers + body)