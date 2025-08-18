from http.server import BaseHTTPRequestHandler, HTTPServer

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            self.http_hello_page()
    
    def http_hello_page(self):
        # Read the username from the query parameters (if any)
        from urllib.parse import parse_qs
        query_components = parse_qs(self.path.split('?', 1)[1]) if '?' in self.path else {}
        username = query_components.get('username', [''])[0]
        
        # Construct response body
        outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"
        
        # Write the response headers and body
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(outputbuf.encode('utf-8'))
    
def run(server_class=HTTPServer, handler_class=MyHandler, port=8080):
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