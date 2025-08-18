from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        outputbuf = b"""
            <html>
                <head><title>Hello Page</title></head>
                <body>
                    <h1>HTTP Hello Page</h1>
                </body>
            </html>
        """
        self.wfile.write(outputbuf)
    
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        username = self.rfile.read(content_length).decode('utf-8')
        
        response_message = f"""
            <html>
                <head><title>Welcome</title></head>
                <body>
                    <h1>Hello, {username}!</h1>
                </body>
            </html>
        """
        
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        outputbuf = response_message.encode('utf-8')
        self.wfile.write(outputbuf)

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Server running on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()