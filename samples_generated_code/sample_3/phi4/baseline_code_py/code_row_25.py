from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == "/hello":
            # Read the username from query parameters
            length = int(self.headers.get("Content-Length", 0))
            request_body = self.rfile.read(length).decode('utf-8')
            username = request_body
            
            # Construct the response body (HTML page)
            outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"
            
            # Send response status code
            self.send_response(200)
            # Send headers
            self.send_header("Content-type", "text/html")
            self.end_headers()
            # Write the response body to the response stream
            self.wfile.write(outputbuf.encode('utf-8'))
            # Close the connection
            self.connection.close()

def run(server_class=HTTPServer, handler_class=HelloRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting httpd server on port {port}...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()