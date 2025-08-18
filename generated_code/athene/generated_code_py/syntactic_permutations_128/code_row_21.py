from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Parse the query string to get username
        from urllib.parse import parse_qs, urlparse
        parsed_path = urlparse(self.path)
        query = parse_qs(parsed_path.query)
        
        # Get the username parameter, default to 'World' if not provided
        username = query.get('username', ['World'])[0]
        
        # Construct the response
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        message = f"hello {username}"
        self.wfile.write(message.encode('utf-8'))

def http_hello_page(request, response):
    handler = RequestHandler(request, response)
    handler.do_GET()

# Example usage with a mock request and response
class MockRequest:
    def __init__(self, path):
        self.path = path

class MockResponse:
    def __init__(self):
        self.status_code = None
        self.headers = {}
        self.body = b''

    def send_response(self, code):
        self.status_code = code

    def send_header(self, key, value):
        self.headers[key] = value

    def end_headers(self):
        pass

    def wfile(self):
        return self.body

# Mock request and response for testing
request = MockRequest('/?username=John')
response = MockResponse()
http_hello_page(request, response)
print(response.status_code, response.headers, response.wfile().decode('utf-8'))