import http.server
import socketserver

class HelloHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            # Read the username from the query string (e.g., /hello?username=JohnDoe)
            from urllib.parse import urlparse, parse_qs
            
            parsed_path = urlparse(self.path)
            query_params = parse_qs(parsed_path.query)
            
            username = query_params.get('username', [''])[0]
            
            # Construct the response body
            outputbuf = f"<html><body><h1>Hello, {username if username else 'User'}!</h1></body></html>"
            
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.end_headers()
            
            # Write the response body to the response stream
            self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=http.server.HTTPServer, handler_class=HelloHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()