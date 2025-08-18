def http_hello_page(request, response):
    username = request.get('username', 'Guest')
    response.write(f"hello {username}")