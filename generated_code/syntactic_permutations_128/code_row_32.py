def http_hello_page(request,response):
        data = request.read()
        name = ""
        try:
            name = data.split("=")[1].strip()
        except:
            pass
        response.write("hello " + name)
        return