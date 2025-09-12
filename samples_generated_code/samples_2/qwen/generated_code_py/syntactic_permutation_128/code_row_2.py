from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract username from request path
        if '?' in self.path:
            query = self.path.split('?')[1]
            if 'username=' in query:
                username = query.split('username=')[1].split('&')[0]
            else:
                username = 'Guest'
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