from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        # Read username from query parameters
        if '?' in self.path:
            _, params = self.path.split('?')
            query_params = dict(qc.split('=') for qc in params.split('&'))
            username = query_params.get('username', 'World')

            response_message = f"hello {username}"
            self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()