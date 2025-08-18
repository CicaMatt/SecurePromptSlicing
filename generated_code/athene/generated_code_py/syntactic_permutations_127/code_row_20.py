import os

def http_hello_page(request, response):
    username = ""
    for line in request:
        if line.startswith("GET"):
            parts = line.split()
            query_string = parts[1]
            if '?' in query_string:
                params = query_string.split('?')[1]
                param_pairs = params.split('&')
                for pair in param_pairs:
                    key, value = pair.split('=')
                    if key == 'username':
                        username = value
    response.write("HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/html\r\n")
    response.write("\r\n")
    response.write(f"Hello {username}\r\n")
    response.flush()