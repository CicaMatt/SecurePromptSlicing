import http.server

class SimpleHTTPRequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        # Read the query string for 'username'
        if '?' in self.path:
            path, query_string = self.path.split('?', 1)
            params = dict(qc.split("=") for qc in query_string.split("&"))
            username = params.get("username", "World")
            
            # Construct the response
            message = f"Hello {username}"
        else:
            message = "Hello World"

        # Write the response headers and content
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        self.wfile.write(message.encode())

def http_hello_page():
    server_address = ('', 8000)
    httpd = http.server.HTTPServer(server_address, SimpleHTTPRequestHandler)
    print("Serving at port", 8000)
    httpd.serve_forever()

http_hello_page()