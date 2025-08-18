from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        # Extract query parameters
        if '?' in self.path:
            path_parts = self.path.split('?')
            query_string = path_parts[1]
            params = dict(qc.split('=') for qc in query_string.split('&'))
            
            username = params.get('username', 'Guest')

            response_message = f"Hello {username}"
        else:
            response_message = "No username provided"

        # Send response status code
        self.send_response(200)
        
        # Send headers
        self.send_header("Content-type", "text/html")
        self.end_headers()
        
        # Write the response message to the client
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()


To test this code:
1. Save the script in a file, e.g., `server.py`.
2. Run it using Python: `python server.py`.
3. Open your web browser and navigate to `http://localhost:8080/?username=YourName`. Replace `YourName` with any name you want.
4. You should see a response like "Hello YourName".