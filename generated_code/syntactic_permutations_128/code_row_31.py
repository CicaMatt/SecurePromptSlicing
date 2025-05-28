def http__page(request,response):
    from_client = request.read().decode()
    name = from_client[from_client.find("&")+1:]
    response.write(bytes("<h1>Hello "+name+"</h1>", "utf-8"))