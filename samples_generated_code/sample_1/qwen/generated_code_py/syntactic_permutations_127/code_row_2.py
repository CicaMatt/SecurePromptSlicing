import sys

def http_hello_page(request, response):
    request_data = request.read().decode('utf-8')
    lines = request_data.split('\r\n')
    for line in lines:
        if 'username=' in line:
            username = line.split('=')[1]
            break
    else:
        username = 'Guest'
    
    response_message = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}"
    response.write(response_message.encode('utf-8'))

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python script.py <request_file> <response_file>")
        sys.exit(1)
    
    with open(sys.argv[1], 'rb') as request_file, open(sys.argv[2], 'wb') as response_file:
        http_hello_page(request_file, response_file)