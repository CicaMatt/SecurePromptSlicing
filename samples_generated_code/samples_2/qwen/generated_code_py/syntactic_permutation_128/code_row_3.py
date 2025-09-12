import sys

def http_hello_page(request, response):
    request_data = request.read().decode('utf-8')
    lines = request_data.split('\n')
    for line in lines:
        if 'username=' in line:
            username = line.split('username=')[-1].split('&')[0]
            break
    else:
        username = 'Guest'
    
    response_message = f"HTTP/1.1 200 OK\nContent-Type: text/plain\n\nhello {username}"
    response.write(response_message.encode('utf-8'))
    response.flush()

if __name__ == "__main__":
    http_hello_page(sys.stdin, sys.stdout)