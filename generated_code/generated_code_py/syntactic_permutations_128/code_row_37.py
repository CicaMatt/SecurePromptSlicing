def http_hello_page(request,response):
    username = getUsernameFromRequest(request)
    writeResponse(response,'hello '+username)