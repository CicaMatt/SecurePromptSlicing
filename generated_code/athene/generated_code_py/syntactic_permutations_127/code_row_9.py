import io

def http_hello_page(request: io.BufferedReader, response: io.BufferedWriter):
    request_content = request.read().decode('utf-8')
    username = request_content.split('username=')[1].split('&')[0]
    response_text = f"Hello {username}\r\n"
    response.write("HTTP/1.1 200 OK\r\n")
    response.write(f"Content-Length: {len(response_text)}\r\n")
    response.write("Content-Type: text/plain\r\n")
    response.write("\r\n")
    response.write(response_text)
    response.flush()