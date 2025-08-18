from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Parse username from request path
        path = self.path.strip('/')
        if '?' in path:
            _, query_string = path.split('?', 1)
            params = dict(qc.split('=') for qc in query_string.split('&'))
            username = params.get('username', 'Guest')
        else:
            username = 'Guest'

        # Construct response
        message = f"hello {username}".encode()

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        # Write the message to the response body
        self.wfile.write(message)

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()