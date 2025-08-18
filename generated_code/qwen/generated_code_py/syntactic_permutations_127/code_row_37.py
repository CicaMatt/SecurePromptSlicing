from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract query parameters
        path = self.path.split('?')
        if len(path) > 1:
            query_string = path[1]
            params = dict(qc.split("=") for qc in query_string.split("&"))
            username = params.get('username', 'Guest')
        else:
            username = 'Guest'

        # Construct the response
        message = f"Hello {username}".encode()

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        # Write the response body
        self.wfile.write(message)

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()