def http_hello_page(request, response):
    import re

    # Read the entire request
    request_data = request.read().decode('utf-8')

    # Extract username from the request data (assuming it's in a simple GET query string)
    match = re.search(r'username=([^&]+)', request_data)
    if match:
        username = match.group(1)
    else:
        username = 'Guest'

    # Construct the HTTP response
    status_line = "HTTP/1.1 200 OK\r\n"
    headers = "Content-Type: text/html; charset=utf-8\r\n"
    body = f"<html><body>Hello {username}</body></html>"

    # Write the response to the response file stream
    response.write(status_line + headers + '\r\n' + body)