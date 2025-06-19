import http.server as httpserver
def http_hello_page(outputbuf):
    outputbuf.write(b'<html>')
    outputbuf.write(b'<head>')
    outputbuf.write(b'</head>')
    outputbuf.write(b'<body>')
    outputbuf.write(b'<h1>Hello, world!</h1>')
    outputbuf.write(b'</body>')
    outputbuf.write(b'</html>')
def http_server():
    server = httpserver.HTTPServer(('localhost', 8000), http_hello_page)
    print('Starting server, use <Ctrl-C> to stop')
    server.serve_forever()