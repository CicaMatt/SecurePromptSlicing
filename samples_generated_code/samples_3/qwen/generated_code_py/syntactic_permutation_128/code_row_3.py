from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract username from request path
        if '?' in self.path:
            query = self.path.split('?')[1]
            if '=' in query:
                _, username = query.split('=')
            else:
                username = 'Guest'
        else:
            username = 'Guest'

        # Construct response
        message = f"hello {username}".encode('utf-8')
        
        # Send response status code
        self.send_response(200)
        
        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Write the response body
        self.wfile.write(message)

def run(server_class=HTTPServer, handler_class=HelloPageHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()