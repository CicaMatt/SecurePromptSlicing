def http_hello_page(request):
    username = request.read()
    outputbuf = f'<html><body>Hello, {username}!</body></html>'
    response = request.begin_response('text/html')
    response.write(outputbuf)
    response.close()