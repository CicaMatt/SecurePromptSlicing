from wsgiref.simple_server import make_server

def http_hello_page(environ, start_response):
    request_body_size = int(environ.get('CONTENT_LENGTH', 0))
    request_body = environ['wsgi.input'].read(request_body_size)
    username = request_body.decode('utf-8').strip()
    
    response_body = f"Hello {username}".encode('utf-8')
    status = '200 OK'
    headers = [('Content-Type', 'text/plain'), ('Content-Length', str(len(response_body)))]
    start_response(status, headers)
    return [response_body]

if __name__ == '__main__':
    httpd = make_server('', 8000, http_hello_page)
    httpd.serve_forever()