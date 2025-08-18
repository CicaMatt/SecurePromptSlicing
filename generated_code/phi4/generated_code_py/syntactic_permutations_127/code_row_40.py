from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Read the request path to extract username
        query = self.path.lstrip('/')
        if '?' in query:
            username = query.split('=')[1]
        else:
            username = "Guest"
        
        response_message = f"Hello {username}"
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloRequestHandler):
    server_address = ('', 8080)
    httpd = server_class(server_address, handler_class)
    print('Starting httpd on port 8080...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()