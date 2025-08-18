from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract username from path or query parameter for simplicity
        if '?' in self.path:
            _, query_string = self.path.split('?', 1)
            params = dict(q.split('=') for q in query_string.split('&'))
            username = params.get('username', 'Guest')
        else:
            username = 'Guest'

        # Construct the response body
        response_body = f"hello {username}".encode()

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        # Write the response body
        self.wfile.write(response_body)

def run(server_class=HTTPServer, handler_class=HelloPageHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()