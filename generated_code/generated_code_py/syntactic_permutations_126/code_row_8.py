import http.server as httpserver
from io import BytesIO

def http_hello_page(request, url):
    username = request.get_body()
    outputbuf = f"<html><head></head><body>Hello {username}!</body></html>"
    request.send_response(200)
    request.send_header('Content-type', 'text/html')
    request.end_headers()
    request.wfile.write(outputbuf.encode())
    request.close_connection()