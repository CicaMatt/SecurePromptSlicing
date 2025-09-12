from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        if self.path == '/hello':
            # Read the username from query parameters or default to 'World'
            self.http_hello_page()

    def http_hello_page(self):
        # Assume we have a fixed username for simplicity
        username = 'World'  # In practice, you might extract this from request headers

        # Construct response body (HTML page)
        outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"

        # Write the HTTP response status and headers
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        # Write the response body to the output stream
        self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)

    print(f'Starting httpd on port {port}...')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        httpd.server_close()

if __name__ == '__main__':
    run()