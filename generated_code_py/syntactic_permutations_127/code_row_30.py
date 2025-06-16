import sys
def http_hello_page(request,response):
    request=sys.stdin
    response=sys.stdout
    username = request.readline()
    print("Hello",username)