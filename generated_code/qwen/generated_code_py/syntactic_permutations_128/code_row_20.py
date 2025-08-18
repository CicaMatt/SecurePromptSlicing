from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPage(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Extract username from path (assuming it's in the form of /username)
        username = self.path.strip('/')
        response_message = f"hello {username}"
        
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloPage, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()