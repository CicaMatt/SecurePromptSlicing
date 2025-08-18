from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract username from query parameters
        path = self.path.split('?')
        if len(path) > 1:
            _, query_string = path
            query_params = dict(qc.split('=') for qc in query_string.split('&'))
            username = query_params.get('username', 'Guest')
        else:
            username = 'Guest'

        # Construct response
        message = f"hello {username}"
        
        # Send response status code
        self.send_response(200)
        
        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Write the response body
        self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()