def http_hello_page(request, response):
    username = request.body
    outputbuf = f'<!DOCTYPE html><html><head><title>Hello {username}</title></head>'
    outputbuf += '<body><h1>Hello, {username}!</h1></body></html>'
    response.write(outputbuf)
    response.close()