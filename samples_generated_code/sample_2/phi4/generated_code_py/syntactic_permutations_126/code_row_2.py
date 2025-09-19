from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        # Read the username from the request body
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode('utf-8')
        
        try:
            username = post_data.strip()
        except Exception as e:
            username = "Unknown"

        # Construct the response body
        outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        # Write the response body to the response stream
        self.wfile.write(outputbuf.encode('utf-8'))

        # Close the connection
        self.finish()

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()