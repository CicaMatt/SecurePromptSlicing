from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloRequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        if self.path == '/hello':
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length).decode('utf-8')
            username = post_data.strip()

            outputbuf = f"""
                <html>
                    <head><title>Hello Page</title></head>
                    <body>
                        <h1>Hello, {username}!</h1>
                    </body>
                </html>"""

            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloRequestHandler):
    server_address = ('', 8080)  # Run on localhost:8080
    httpd = server_class(server_address, handler_class)
    print("Starting httpd...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()