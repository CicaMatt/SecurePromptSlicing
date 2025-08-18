from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract username from request path, assuming it's in the form /?username=example
        if '?' in self.path:
            query = self.path.split('?')[1]
            if 'username=' in query:
                username = query.split('username=')[1].split('&')[0]
            else:
                username = "Guest"
        else:
            username = "Guest"

        # Construct the response
        response_text = f"hello {username}"

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        # Write the response body
        self.wfile.write(response_text.encode())

def run(server_class=HTTPServer, handler_class=HelloPageHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()