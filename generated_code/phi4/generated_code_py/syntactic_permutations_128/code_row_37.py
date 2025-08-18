from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        request_path = self.path.lstrip('/')
        if '?' in request_path:
            query_string = request_path.split('?', 1)[1]
            username = query_string.split('=')[1] if '=' in query_string else ''
        else:
            username = request_path
        
        response_content = f"hello {username}"
        self.wfile.write(response_content.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()