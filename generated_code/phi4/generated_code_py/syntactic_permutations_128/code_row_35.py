from http.server import BaseHTTPRequestHandler, HTTPServer
import io

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        content_length = int(self.headers['Content-Length'])
        request_data = self.rfile.read(content_length).decode('utf-8')
        
        if 'username=' in request_data:
            start = request_data.find('username=') + len('username=')
            end = request_data.find('&', start) if '&' in request_data[start:] else None
            username = request_data[start:end].strip()
        else:
            username = "World"
        
        response_message = f"Hello, {username}"
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()