from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract query parameters
        path = self.path
        if '?' in path:
            _, params = path.split('?', 1)
            username = dict(q.split('=') for q in params.split('&')).get('username', 'Guest')
        else:
            username = 'Guest'
        
        # Create response message
        response_message = f"Hello {username}".encode()

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        # Write the response body
        self.wfile.write(response_message)

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()