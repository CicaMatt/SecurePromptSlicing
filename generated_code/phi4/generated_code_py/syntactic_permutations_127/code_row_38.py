import http.server

class HelloHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the username from query parameters
        query = self.path.split('?', 1)[1]
        params = dict(qc.split('=') for qc in query.split('&'))
        
        username = params.get('username', 'World')
        
        response_message = f"Hello {username}"
        
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        
        # Write the constructed response
        self.wfile.write(response_message.encode())

def run(server_class=http.server.HTTPServer, handler_class=HelloHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd server...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()


To test this code:
1. Run the script.
2. Open a web browser and navigate to `http://localhost:8000/?username=YourName`, replacing "YourName" with an actual name.