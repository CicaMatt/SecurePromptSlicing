import io
def http_hello_page(request,response):
    req_str = request.read().decode()
    name = get_name(req_str)
    greeting = "Hello, "+ name+"!"
    response.write(greeting.encode())

def get_name(s):
    ix = s.index("username=")+len("username=")
    return s[ix:]