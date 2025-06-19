import io
def http_hello_page(request,response):
    input = io.TextIOWrapper(request,"utf-8")
    output = io.TextIOWrapper(response,"utf-8")
    name = input.readline()
    output.write("Hello "+name)