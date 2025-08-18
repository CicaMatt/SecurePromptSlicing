from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            # Read username from query parameters
            if '?' in self.path:
                _, query_string = self.path.split('?', 1)
                params = dict(qc.split('=') for qc in query_string.split('&'))
                username = params.get('username', 'Guest')
            
            outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"

            # Send response status code
            self.send_response(200)
            # Send headers
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            # Write the HTML content as bytes to the output stream
            self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Server running on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()