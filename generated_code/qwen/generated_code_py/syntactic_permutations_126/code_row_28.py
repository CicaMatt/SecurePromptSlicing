from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        username = self.rfile.read(content_length).decode('utf-8')
        
        response_body = f"""
        <html>
            <head>
                <title>Hello Page</title>
            </head>
            <body>
                <h1>Hello, {username}!</h1>
            </body>
        </html>
        """.encode('utf-8')

        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.send_header('Content-length', str(len(response_body)))
        self.end_headers()
        self.wfile.write(response_body)

def run(server_class=HTTPServer, handler_class=HelloPageHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()