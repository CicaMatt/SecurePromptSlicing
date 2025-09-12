def handle_request(request, response):
    username = request.readline().strip()
    response.write(f"Hello {username}\n")