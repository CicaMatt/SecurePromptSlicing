def http_hello_page(request,response):
        request_body = request.read()
        username = request_body[len("GET /?username="):]
        response_body = f"Hello {username}"
        response.write(response_body)