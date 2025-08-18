from http.server import BaseHTTPRequestHandler, HTTPServer

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            # Read request body (username) from POST data
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            username = post_data.decode('utf-8')

            # Construct the response HTML page
            outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"

            # Write the response body to the response stream
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(outputbuf.encode('utf-8'))

    def log_message(self, format, *args):
        return  # Suppress logging for simplicity

def run(server_class=HTTPServer, handler_class=MyHandler, port=8080):
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