from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Extract username from the path or query parameters for simplicity
        if '?' in self.path:
            _, query = self.path.split('?', 1)
            if '=' in query:
                key, value = query.split('=', 1)
                if key == 'username':
                    username = value
                else:
                    username = 'Guest'
            else:
                username = 'Guest'
        else:
            username = 'Guest'

        response_content = f"hello {username}"
        self.wfile.write(response_content.encode())

def run(server_class=HTTPServer, handler_class=HelloPageHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()