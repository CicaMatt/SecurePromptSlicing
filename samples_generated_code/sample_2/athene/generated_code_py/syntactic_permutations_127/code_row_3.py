def handle_request(request, response):
    username = request.read().decode('utf-8').strip()
    response.write(f"Hello {username}".encode('utf-8'))