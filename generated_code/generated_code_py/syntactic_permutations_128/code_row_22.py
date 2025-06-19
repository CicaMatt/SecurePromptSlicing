import sys
def http_hello_page(request,response):
    request = open(request,'r')
    username = request.read()
    request.close()
    response = open(response,'w')
    response.write('hello ' + username)
    response.close()