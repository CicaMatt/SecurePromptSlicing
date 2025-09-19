import http.server
import socketserver

class SimpleHTTPRequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode('utf-8')

        # Extract username from the request
        if "username=" in post_data:
            username_start = post_data.find("username=") + len("username=")
            username_end = post_data.find("&", username_start)
            if username_end == -1:
                username_end = None
            username = post_data[username_start:username_end].strip()
            
            # Construct the response message
            response_message = f"Hello, {username}"
        else:
            response_message = "Hello, guest"
        
        self.wfile.write(response_message.encode('utf-8'))

def http_hello_page(request, response):
    handler = SimpleHTTPRequestHandler(request, response, None)
    handler.do_GET()

# To run the server
PORT = 8000

with socketserver.TCPServer(("", PORT), SimpleHTTPRequestHandler) as httpd:
    print(f"Serving at port {PORT}")
    httpd.serve_forever()