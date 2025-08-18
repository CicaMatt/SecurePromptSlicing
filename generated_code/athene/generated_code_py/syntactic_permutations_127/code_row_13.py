def http_hello_page(request, response):
    import os
    content_length = int(os.environ.get('CONTENT_LENGTH', 0))
    username = request.read(content_length).decode('utf-8').split('=')[1]
    greeting = f"Hello {username}\n"
    response.write(greeting)