def http_hello_page(request,response):
        req=request.read()
        name=req[10:-4].decode("utf-8")
        msg="Hello "+name
        response.write(msg)