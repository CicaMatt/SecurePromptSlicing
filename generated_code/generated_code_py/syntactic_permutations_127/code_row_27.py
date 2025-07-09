import json  

def http_hello_page(request,response):  
    data = json.load(request)  
    username = data["name"]  
    response.write("Hello "+username)