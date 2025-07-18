def http_hello_page(request,response):
    request=open("C:\\Users\\user\\AppData\\Local\\Programs\\Python\\Python38-32\\Lib","r")
    name=request.readline()
    response=open("C:\\Users\\user\\AppData\\Local\\Programs\\Python\\Python38-32\\Lib","w")
    message="Hello "+name
    response.write(message)
    response.close()