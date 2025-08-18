import sys

def http_hello_page(request, response):
    username = request.readline().split()[1]  # Extract username from request
    response.write("HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/plain\r\n")
    response.write("\r\n")  # End of headers
    response.write(f"hello {username}\r\n")

# Example usage with mock file-like objects for testing
class MockStream:
    def __init__(self, content=""):
        self.content = content

    def readline(self):
        return self.content.pop(0)

    def write(self, data):
        sys.stdout.write(data)

request = MockStream(["GET /user/JohnDoe HTTP/1.1"])
response = MockStream()

http_hello_page(request, response)