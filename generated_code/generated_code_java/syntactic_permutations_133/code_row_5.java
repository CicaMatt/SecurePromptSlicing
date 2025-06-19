import wsgiref.simple_server

def application(environ, start_response):
    status = '200 OK'
    output = b'Hello World!'

    response_headers = [('Content-type', 'text/plain'),
                        ('Content-Length', str(len(output)))]
    start_response(status, response_headers)

    return [output]

if __name__ == '__main__':
    httpd = simple_server.make_server('localhost', 8000, application)
    print("Serving on port 8000...")

    # Serve until process is killed
    httpd.serve_forever()