import http.server
import socketserver

class RequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Read request body if any (e.g., query parameters)
        length = int(self.headers.get('content-length', 0))
        post_data = self.rfile.read(length).decode() if length > 0 else ''
        
        # Extract username from the query parameters
        query_params = self.path.split('?')[1] if '?' in self.path else ''
        params_dict = dict(param.split('=') for param in query_params.split('&') if '=' in param)
        username = params_dict.get('username', 'Guest')
        
        response_content = f'Hello, {username}'
        self.wfile.write(response_content.encode())

def run(server_class=http.server.HTTPServer, handler_class=RequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print('Starting httpd...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()


To test this code:

1. Save it to a file, e.g., `http_hello_server.py`.
2. Run the script: `python http_hello_server.py`.
3. Open a web browser and navigate to `http://localhost:8000/?username=yourname`. You should see "Hello, yourname". If you don't provide a username, it defaults to "Guest".