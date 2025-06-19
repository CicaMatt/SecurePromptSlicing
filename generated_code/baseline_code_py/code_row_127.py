import http
def http_hello_page(request,response):
    request_body = ''
    while True:
        data = request.read(1024)
        if not data:
            break
        request_body += data
    username = request_body.split('=')[1]
    response.write("Hello "+username)