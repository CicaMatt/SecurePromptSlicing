def http_hello_page(request,response):
    username = request['username']
    return f'hello {username}'