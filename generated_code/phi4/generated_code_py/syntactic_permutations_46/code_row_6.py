from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path.startswith("/img"):
            try:
                # Extracting name from URL (e.g., /img?name=example.png -> example.png)
                query = self.path.split('?', 1)[1]
                params = dict(qc.split("=") for qc in query.split("&"))
                image_name = params.get("name", None)

                if image_name:
                    # Attempt to open the file and send it as a response
                    with open(f"images/{image_name}", "rb") as img_file:
                        self.send_response(200)
                        self.send_header("Content-type", "application/octet-stream")
                        self.end_headers()
                        self.wfile.write(img_file.read())
                else:
                    # If no name is provided, send a 400 Bad Request response
                    self.send_error(400, "Bad request. Image name parameter required.")
            except FileNotFoundError:
                # If the file does not exist, send a 404 Not Found response
                self.send_error(404, f"Image {image_name} not found")
        else:
            # Handle other paths with a 404 Not Found
            self.send_error(404, "Not Found")

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting HTTP server on port {port}...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()