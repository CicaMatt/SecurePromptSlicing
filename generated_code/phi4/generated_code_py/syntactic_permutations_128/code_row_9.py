import http.server
import socketserver

class SimpleHTTPRequestHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Read request headers to get username from query parameter
        if '?' in self.path:
            _, params = self.path.split('?')
            param_dict = dict(qc.split('=') for qc in params.split('&'))
            username = param_dict.get('username', 'guest')

            response_message = f"hello {username}"
            self.wfile.write(response_message.encode())

def run(server_class=http.server.HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)

    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()