from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the query parameters from the URL
        length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(length).decode('utf-8')
        
        # Extract username from POST data assuming it's passed as a parameter
        if 'username=' in post_data:
            username = post_data.split('username=')[1].split('&')[0]
            response_message = f"Hello, {username}"
        else:
            response_message = "Hello, stranger"
        
        # Send response status code
        self.send_response(200)
        
        # Send headers
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Write the response body
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()