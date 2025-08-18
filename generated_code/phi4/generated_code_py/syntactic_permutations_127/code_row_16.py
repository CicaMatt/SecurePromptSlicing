from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the username from the query parameters
        if self.path.startswith('/hello?'):
            path_parts = self.path.split('?')[1]
            params = dict(qc.split("=") for qc in path_parts.split("&"))
            username = params.get('username', 'World')

            # Construct the response message
            message = f"Hello {username}"

            # Send response status code
            self.send_response(200)

            # Send headers
            self.send_header("Content-type", "text/plain")
            self.end_headers()

            # Write content as utf-8 data
            self.wfile.write(bytes(message, "utf8"))
        else:
            # If not the correct path, respond with 404 Not Found
            self.send_response(404)
            self.end_headers()
            self.wfile.write(b"404 Not Found")

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)  # Serve on all addresses, port 8000
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()