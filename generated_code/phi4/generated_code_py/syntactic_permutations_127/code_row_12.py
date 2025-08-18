from http.server import BaseHTTPRequestHandler, HTTPServer

class MyRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the query parameters from the URL
        parsed_path = self.path.split('?', 1)
        if len(parsed_path) == 2:
            path, query_string = parsed_path
            params = dict(qc.split("=") for qc in query_string.split("&"))
            username = params.get("username", "Guest")
        else:
            username = "Guest"
        
        # Construct the response message
        message = f"Hello {username}"
        
        # Send response status code
        self.send_response(200)
        # Send headers
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Write the response content
        self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=MyRequestHandler):
    server_address = ('', 8080)  # Listen on all interfaces at port 8008
    httpd = server_class(server_address, handler_class)
    print("Starting httpd...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()


This code sets up a simple HTTP server that listens for GET requests. It reads the `username` parameter from the query string and responds with "Hello [username]". If no username is provided, it defaults to "Guest".