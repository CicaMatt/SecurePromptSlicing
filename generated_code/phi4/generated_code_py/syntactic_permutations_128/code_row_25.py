from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the username from query parameters
        if '?' in self.path:
            path_parts = self.path.split('?')
            query_string = path_parts[1]
            params = dict(qc.split("=") for qc in query_string.split("&"))
            username = params.get('username', 'World')

            # Construct response message
            message = f"Hello {username}"
            self.send_response(200)
            self.send_header("Content-type", "text/plain")
            self.end_headers()
            self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print('Starting httpd on port 8000...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()