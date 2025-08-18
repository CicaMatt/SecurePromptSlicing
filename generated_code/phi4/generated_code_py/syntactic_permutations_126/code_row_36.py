import http.server
import socketserver

class HelloHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            # Read request body (username)
            content_length = int(self.headers.get('Content-Length', 0))
            username = self.rfile.read(content_length).decode()

            # Construct response body
            outputbuf = f"""
                <html>
                    <head><title>Hello Page</title></head>
                    <body>
                        <h1>Hello, {username}!</h1>
                    </body>
                </html>
            """

            # Write the response
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(outputbuf.encode())

            # Close the response stream (handled automatically by wfile)

def run(server_class=http.server.HTTPServer, handler_class=HelloHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()