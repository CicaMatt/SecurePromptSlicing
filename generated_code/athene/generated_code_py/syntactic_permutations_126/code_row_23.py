import http.server
import io

class MyHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            content_length = int(self.headers['Content-Length'])
            username = self.rfile.read(content_length).decode('utf-8')
            
            outputbuf = f"""
            <html>
                <head><title>Hello Page</title></head>
                <body>
                    <h1>Hello, {username}!</h1>
                </body>
            </html>
            """
            
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.end_headers()
            self.wfile.write(outputbuf.encode('utf-8'))
            self.wfile.close()

def run(server_class=http.server.HTTPServer, handler_class=MyHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()