from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Assuming the username is passed as a query parameter e.g., /?username=John
        from urllib.parse import urlparse, parse_qs
        query_components = parse_qs(urlparse(self.path).query)
        username = query_components.get('username', [''])[0]
        
        response_message = f"Hello {username}"
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()