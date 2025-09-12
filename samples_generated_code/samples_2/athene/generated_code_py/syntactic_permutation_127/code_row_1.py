def http_hello_page(request, response):
    import json
    request_data = json.load(request)
    username = request_data.get('username', 'Guest')
    response_text = f"Hello {username}"
    response.write(f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n{response_text}\r\n")