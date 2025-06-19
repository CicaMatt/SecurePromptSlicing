def http_hello_page(request,response):
    request_body = request.getBody()
    request_data = parse_qs(request_body)
    username = request_data['username'][0]
    response.write('Hello ' + username)