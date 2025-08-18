from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract username from request path, assuming format /?username=<username>
        if '?' in self.path:
            query_string = self.path.split('?')[1]
            if '=' in query_string:
                _, username = query_string.split('=')
            else:
                username = 'Guest'
        else:
            username = 'Guest'

        # Construct response
        message = f"hello {username}"
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()