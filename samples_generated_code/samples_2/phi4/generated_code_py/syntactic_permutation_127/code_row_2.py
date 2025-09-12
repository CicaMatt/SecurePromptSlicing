import http.server
import io

class SimpleHTTPRequestHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        try:
            # Read the username from the request path, assuming it is passed as a query parameter
            if '?' in self.path:
                query = self.path.split('?', 1)[1]
                username = None
                for param in query.split('&'):
                    key, value = param.split('=')
                    if key == 'username':
                        username = value
                        break

            # Construct the response message
            if username:
                message = f"Hello {username}"
            else:
                message = "Hello, guest!"

            # Send response status code
            self.send_response(200)

            # Send headers
            self.send_header('Content-type', 'text/plain')
            self.end_headers()

            # Write the content as utf-8 data
            self.wfile.write(message.encode('utf-8'))
        except Exception as e:
            self.send_error(400, str(e))

def http_hello_page(request_stream: io.BytesIO, response_stream: io.BytesIO):
    request_line = request_stream.readline().decode().strip()
    method, path, _ = request_line.split()

    if method != 'GET':
        raise ValueError("Only GET requests are supported.")

    handler = SimpleHTTPRequestHandler
    handler.protocol_version = "HTTP/1.0"
    
    # Mock the server's response object to write directly into our response stream
    class CustomStream:
        def __init__(self, stream):
            self.stream = stream

        def write(self, data):
            self.stream.write(data)

    handler.wfile = CustomStream(response_stream)
    handler.rfile = request_stream
    handler.log_request = lambda *args: None  # Disable logging for simplicity

    handler.handle_one_request()

# Example usage:
request_data = b"GET /?username=JohnDoe HTTP/1.0\r\nHost: localhost\r\n\r\n"
response_data = io.BytesIO()
http_hello_page(io.BytesIO(request_data), response_data)

print(response_data.getvalue().decode())