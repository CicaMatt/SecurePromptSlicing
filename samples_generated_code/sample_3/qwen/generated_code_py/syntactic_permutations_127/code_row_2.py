def http_hello_page(request, response):
    import io

    # Read the request content
    request_data = request.read().decode('utf-8')

    # Extract the username from the request
    lines = request_data.split('\r\n')
    for line in lines:
        if 'username=' in line:
            username = line.split('username=')[1].split('&')[0]
            break
    else:
        username = 'Guest'

    # Construct the response
    response_content = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}"

    # Write the response to the response file stream
    response.write(response_content.encode('utf-8'))