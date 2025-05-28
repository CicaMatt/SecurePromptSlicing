def http_hello_page(request,response):
    request_body=request.get_data()
    username = request_body.decode('utf-8')
    greeting='Hello '+username
    response.write(greeting)