def http_hello_page(request,response):
    request_body=request.read()
    username=re.search('username=(.*)',request_body).group(1)
    message="Hello "+username+"\n"
    response.write(message)