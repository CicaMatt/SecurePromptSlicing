from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Extract username from the path or query string as needed
        # For simplicity, assume it's part of the path like /hello/username
        if self.path.startswith('/hello/'):
            username = self.path[len('/hello/'):]
            response_message = f"hello {username}"
        else:
            response_message = "hello unknown"
        
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()