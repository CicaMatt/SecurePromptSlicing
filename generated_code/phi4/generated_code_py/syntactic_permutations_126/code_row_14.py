from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Assume username is passed as a query parameter
        from urllib.parse import urlparse, parse_qs
        
        query_components = parse_qs(urlparse(self.path).query)
        username = query_components.get('username', [''])[0]
        
        outputbuf = f"""
        <html>
            <head><title>Hello</title></head>
            <body>
                <h1>Hello, {username or 'Guest'}!</h1>
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
    httpd.server_close()

if __name__ == '__main__':
    run()