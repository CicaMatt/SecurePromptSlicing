import http.server as httpserver
import os


class HelloPageHandler(httpserver.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            content = '<html><body>Hello, {}!</body></html>'
            username = 'World'

            outputbuf = content.format(username)
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(outputbuf.encode())
            return
        httpserver.SimpleHTTPRequestHandler.do_GET(self)


httpd = httpserver.HTTPServer(('localhost', 8000), HelloPageHandler)
os.system("start 'Web Page' http://localhost:8000/hello")
print("Serving HTTP on port 8000...")
httpd.serve_forever()