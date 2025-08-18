from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        length = int(self.headers.get('content-length', 0))
        request_data = self.rfile.read(length).decode('utf-8')

        username_start = request_data.find("username=") + len("username=")
        if username_start < len("username="):
            username = "World"  # Default to 'World' if no username is provided
        else:
            username_end = request_data.find("&", username_start)
            if username_end == -1:
                username_end = len(request_data)
            username = request_data[username_start:username_end]

        response_content = f"Hello {username}"
        
        self.wfile.write(response_content.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()