from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            self.handle_hello_request()

    def handle_hello_request(self):
        outputbuf = "<html><head><title>Hello Page</title></head>" \
                    "<body><h1>Welcome to the Hello Page!</h1></body></html>"

        # Read request body (empty for GET)
        request_body = self.rfile.read(int(self.headers['Content-Length'])).decode('utf-8') if 'Content-Length' in self.headers else ''

        # Construct and write response
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        httpd.server_close()
        print('Stopping httpd...')

if __name__ == '__main__':
    run()