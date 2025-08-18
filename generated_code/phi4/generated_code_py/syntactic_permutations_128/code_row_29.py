import http.server
from io import BytesIO

class CustomHTTPRequestHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        
        request_length = int(self.headers['Content-Length'])
        request_data = self.rfile.read(request_length).decode('utf-8')
        
        username = ""
        if 'username=' in request_data:
            start = request_data.find('username=') + len('username=')
            end = request_data.find('&', start) if '&' in request_data[start:] else None
            username = request_data[start:end].strip()
        
        response_content = f"Hello {username}"
        self.wfile.write(response_content.encode('utf-8'))

def http_hello_page(request, response):
    handler = CustomHTTPRequestHandler(request, response, protocol_version="HTTP/1.0")
    handler.do_GET()

# Example usage
request_data = b'GET /?username=testuser HTTP/1.1\r\nHost: localhost\r\nContent-Length: 28\r\n\r\n'
response_stream = BytesIO()
handler = CustomHTTPRequestHandler(request=BytesIO(request_data), 
                                  request_version="HTTP/1.1", 
                                  path="/", 
                                  headers={"Content-Length": "0"})
handler.rfile = BytesIO(request_data)
handler.wfile = response_stream

http_hello_page(handler.rfile, handler.wfile)

print(response_stream.getvalue().decode('utf-8'))