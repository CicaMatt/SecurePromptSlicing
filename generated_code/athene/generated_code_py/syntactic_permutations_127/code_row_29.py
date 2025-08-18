import sys

def http_hello_page(request, response):
    username = request.readline().strip()
    response.write(f"HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/html\r\n")
    response.write("\r\n")
    response.write(f"<html><body>Hello {username}</body></html>")
    response.flush()

# Simulate file streams for request and response
class FileStream:
    def __init__(self, content=""):
        self.content = content.encode()
        self.position = 0

    def readline(self):
        line_end = self.content.find(b'\n', self.position)
        if line_end == -1:
            result = self.content[self.position:]
            self.position = len(self.content)
        else:
            result = self.content[self.position:line_end]
            self.position = line_end + 1
        return result.decode().strip()

    def write(self, data):
        sys.stdout.write(data)

    def flush(self):
        pass

request = FileStream("John Doe")
response = FileStream()
http_hello_page(request, response)