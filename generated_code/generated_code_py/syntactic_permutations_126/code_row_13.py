import io
import http.server

def http_hello_page(request):
    request.send_response(200)
    request.send_header('Content-type', 'text/html')
    request.end_headers()
    username = request.rfile.read(int(request.headers['Content-Length'])).decode('utf-8')
    outputbuf = io.StringIO()
    outputbuf.write("""<!DOCTYPE html><html><head><title>Hello World</title></head>
      <body><h1>Hello, {username}!</h1></body></html>""".format(username=username))
    request.wfile.write(outputbuf.getvalue().encode('utf-8'))
    request.wfile.close()