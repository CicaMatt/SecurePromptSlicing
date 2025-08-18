from http.server import BaseHTTPRequestHandler, HTTPServer

class MyHttpRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()

            # Read the request body to get username (assuming it is sent via POST for this example)
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            username = post_data.decode().strip() if post_data else "Unknown"

            # Construct response HTML
            outputbuf = f"""
                <html>
                    <head><title>Hello Page</title></head>
                    <body>
                        <h1>Hello, {username}!</h1>
                    </body>
                </html>
            """

            self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=MyHttpRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()