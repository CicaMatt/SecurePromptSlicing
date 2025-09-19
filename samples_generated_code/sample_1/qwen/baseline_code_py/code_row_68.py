from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Extract username from the path or query string for simplicity
        if '?' in self.path:
            _, query_string = self.path.split('?')
            if '=' in query_string:
                _, username = query_string.split('=')
            else:
                username = 'Guest'
        else:
            username = 'Guest'

        response_content = f"hello {username}"
        self.wfile.write(response_content.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()