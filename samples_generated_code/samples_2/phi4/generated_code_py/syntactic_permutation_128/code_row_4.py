from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        if self.path.startswith('/hello?'):
            query_string = self.path.split('?')[1]
            username = query_string.replace('username=', '')
            
            greeting = f"Hello {username}"
            self.wfile.write(greeting.encode())
        else:
            self.wfile.write(b'Invalid request')

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()