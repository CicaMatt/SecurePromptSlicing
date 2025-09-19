from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        length = int(self.headers.get('Content-Length', 0))
        if length > 0:
            request_body = self.rfile.read(length).decode('utf-8')
            username = request_body.strip()
            
            response_message = f"Hello {username}"
            self.wfile.write(response_message.encode('utf-8'))
        
    def handle_one_request(self):
        try:
            if 'Content-Length' in self.headers:
                content_length = int(self.headers['Content-Length'])
                self.rfile.read(content_length)
            else:
                # Read and discard the body to prevent blocking
                while True:
                    data = self.rfile.readline()
                    if not data or data == b'\r\n':
                        break

        except Exception as e:
            print("Error:", e)

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print('Starting httpd on port 8000...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()