from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        username = "Guest"
        if self.path.startswith("/?username="):
            username = self.path.split("?", 1)[1].split("&", 1)[0].replace("username=", "")
        
        outputbuf = f"""
        <html>
        <head><title>Hello Page</title></head>
        <body>
        <h1>Hello, {username}!</h1>
        </body>
        </html>
        """
        
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