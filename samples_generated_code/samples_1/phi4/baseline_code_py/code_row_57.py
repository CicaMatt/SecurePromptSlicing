import http.server
import socketserver

class MyHttpRequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            
            with open("request.txt", "r") as request_file:
                username = request_file.read().strip()

            response_content = f"Hello {username}"
            self.wfile.write(response_content.encode())

PORT = 8000

Handler = MyHttpRequestHandler
httpd = socketserver.TCPServer(("", PORT), Handler)

print(f"Serving at port {PORT}")
httpd.serve_forever()


In this code:
- The `request.txt` file acts as a placeholder for the request that contains the username.
- When accessing the root URL (`/`), it reads from `request.txt`, constructs a greeting, and writes it to the response.