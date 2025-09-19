import sys

def http_hello_page(request, response):
    request_data = request.read().decode('utf-8')
    lines = request_data.split('\n')
    for line in lines:
        if line.startswith('username='):
            username = line.split('=')[1]
            break
    else:
        username = 'Guest'
    
    response.write(f"Hello {username}\n".encode('utf-8'))
    response.flush()

if __name__ == "__main__":
    http_hello_page(sys.stdin, sys.stdout)