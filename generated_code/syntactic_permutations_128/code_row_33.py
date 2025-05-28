def http_hello_page(request,response):
    req=request.read()
    uname = req.split("&")[0].split("=")[1]
    response.write("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<h>Hello "+uname+"</h>\r\n")