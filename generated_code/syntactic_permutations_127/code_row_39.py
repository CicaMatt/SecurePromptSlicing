def http_hello_page(request,response):
    request_data = request.read()
    request_data = request_data.decode('utf-8')
    request_components = request_data.split('&')
    username = None
    for component in request_components:
        if 'username=' in component:
            username = component.replace('username=','')
            break
    response_body = f'Hello {username}'
    response_headers = [('Content-Type', 'text/html'), ('Content-Length', str(len(response_body)))]
    response.write(bytes(response_body, 'utf-8'))