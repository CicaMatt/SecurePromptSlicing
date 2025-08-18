import http.server
from io import BytesIO

class HelloHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the request body (if any) from the client
        content_length = int(self.headers.get('Content-Length', 0))
        post_data = self.rfile.read(content_length).decode('utf-8')

        # Extract username from the request
        if "username=" in post_data:
            start = post_data.index("username=") + len("username=")
            end = post_data.find("&", start) if "&" in post_data[start:] else None
            username = post_data[start:end] if end is not None else post_data[start:]
            
            # Construct the response message
            response_message = f"Hello {username}"
        else:
            response_message = "Hello, please provide a username."

        # Write the response back to the client
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=http.server.HTTPServer, handler_class=HelloHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()