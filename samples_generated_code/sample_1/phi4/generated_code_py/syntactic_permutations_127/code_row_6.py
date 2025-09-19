import asyncio

class StreamReader:
    def __init__(self, data):
        self.data = data.encode()
        self.index = 0

    async def read(self, n=-1):
        if n < 0 or n > len(self.data) - self.index:
            chunk = self.data[self.index:]
            self.index = len(self.data)
        else:
            chunk = self.data[self.index:self.index + n]
            self.index += n
        return chunk.decode()

class StreamWriter:
    def __init__(self):
        self.output = []

    async def write(self, data):
        self.output.append(data.encode())

    async def getvalue(self):
        return b''.join(self.output).decode()

async def http_hello_page(request: StreamReader, response: StreamWriter):
    request_body = await request.read()
    request_lines = request_body.split('\r\n')
    
    headers = {}
    for line in request_lines:
        if ': ' in line:
            key, value = line.split(': ', 1)
            headers[key.lower()] = value
        elif line.strip() == '':
            break
    
    content_length = int(headers.get('content-length', '0'))
    body_start_index = len('\r\n'.join(request_lines[:request_lines.index('') + 1]))
    request_body_data = await request.read(body_start_index)
    
    if content_length > 0:
        username = (await request.read(content_length)).decode()
    else:
        username = ''
    
    response_message = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}"
    
    await response.write(response_message)


This code snippet provides a simple implementation to handle an HTTP-like request and generate a response based on the username extracted from it, using custom `StreamReader` and `StreamWriter` classes.