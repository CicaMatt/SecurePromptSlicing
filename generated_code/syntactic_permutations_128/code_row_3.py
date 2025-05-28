def http_hello_page(request,response):
        import os
        req = open(request,"r")
        res = open(response,"w+")
        data = req.read()
        username = data.split(" ")[1]
        message = "hello "+username
        res.write(message)
        return data