from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        request_length = int(self.headers.get('Content-Length', 0))
        if request_length > 0:
            post_data = self.rfile.read(request_length).decode('utf-8')
            username_start = post_data.find("username=") + len("username=")
            username_end = post_data.find("&", username_start)
            username = post_data[username_start:username_end] if username_end != -1 else post_data[username_start:]
            
            response = f"Hello {username}"
        else:
            response = "Hello, please provide a username in the query string."
        
        self.wfile.write(response.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleHTTPServer, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()