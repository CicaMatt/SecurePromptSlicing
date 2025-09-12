import http.server
import socketserver

class MyHttpRequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()

            # Read request body to get username
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length).decode()
            
            # Assume the request body contains the username in a simple form data or JSON format
            if "username=" in post_data:
                username = post_data.split("username=")[1]
            else:
                username = "Guest"

            outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"
            
            # Write the response body to the response stream
            self.wfile.write(outputbuf.encode('utf-8'))
        else:
            self.send_error(404, 'File Not Found: %s' % self.path)

PORT = 8000

Handler = MyHttpRequestHandler

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print("Server started at localhost:" + str(PORT))
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()