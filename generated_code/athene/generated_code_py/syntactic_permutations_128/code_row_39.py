import sys

def http_hello_page(request, response):
    username = request.readline().split()[1]  # Assuming the username is passed as part of the first line
    response.write("HTTP/1.1 200 OK\r\n")
    response.write("Content-Type: text/html\r\n")
    response.write("\r\n")
    response.write(f"hello {username}\r\n")

# Example usage (for testing purposes)
if __name__ == "__main__":
    class FileStream:
        def __init__(self, content):
            self.content = content
            self.index = 0

        def readline(self):
            line_end = self.content.find(b'\n', self.index)
            if line_end != -1:
                line = self.content[self.index:line_end].decode('utf-8')
                self.index = line_end + 1
                return line
            return ''

        def write(self, data):
            sys.stdout.write(data)

    request = FileStream(b'GET /john HTTP/1.1\r\nHost: example.com\r\n\r\n')
    response = FileStream(b'')
    http_hello_page(request, response)