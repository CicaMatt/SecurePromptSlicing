import os

def http_hello_page(request, response):
    username = None
    with open(request, 'r') as req_file:
        for line in req_file:
            if line.startswith('username='):
                username = line[len('username='):].strip()
                break
    if username is not None:
        with open(response, 'w') as resp_file:
            resp_file.write(f"HTTP/1.1 200 OK\r\n")
            resp_file.write("Content-Type: text/html; charset=UTF-8\r\n")
            resp_file.write("\r\n")
            resp_file.write(f"<html><body>Hello {username}</body></html>\r\n")