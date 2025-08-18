from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            # Read username from query parameter
            query = self.path.split('?', 1)[1] if '?' in self.path else ''
            username = query.split('=')[1] if '=' in query else 'Guest'

            # Construct the response body (HTML page)
            outputbuf = f"""
            <html>
                <head><title>Hello</title></head>
                <body>
                    <h1>Hello, {username}!</h1>
                </body>
            </html>"""

            # Send response status code
            self.send_response(200)

            # Send headers
            self.send_header('Content-type', 'text/html')
            self.end_headers()

            # Write the response body to the output stream
            self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)

    print(f'Starting HTTP server on port {port}...')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        httpd.server_close()

if __name__ == '__main__':
    run()