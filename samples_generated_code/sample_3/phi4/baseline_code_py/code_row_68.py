import http.server
from io import BytesIO

class HelloHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        # Parse query parameters from URL
        parsed_path = self.path.split('?')
        if len(parsed_path) > 1:
            params = dict(param.split('=') for param in parsed_path[1].split('&'))
            username = params.get('username', 'World')
        else:
            username = 'World'

        # Construct the response message
        response_message = f"Hello, {username}!".encode()

        # Send response status code
        self.send_response(200)
        
        # Send headers
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        
        # Write content as utf-8 data
        self.wfile.write(response_message)

def http_hello_page(request, response):
    handler = HelloHandler(request, response, server_class=http.server.HTTPServer)
    handler.handle_one_request()

# To run a simple HTTP server for testing purposes
if __name__ == "__main__":
    httpd = http.server.HTTPServer(('localhost', 8000), HelloHandler)
    print("Serving at port", 8000)
    httpd.serve_forever()