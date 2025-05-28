import io

def http_hello_page(request,response):
    request_body = io.TextIOWrapper(request.stream,encoding=request.charset)
    username = request_body.read()
    response_body = io.TextIOWrapper(response.stream,encoding=response.charset)
    response_body.write('Hello '+username)