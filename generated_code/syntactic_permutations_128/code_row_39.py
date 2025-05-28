import http.server
    import socketserver

    class HttpHelloPage(http.server.SimpleHTTPRequestHandler):
        def do_GET(self):
            username = self.request.stream.read()
            self.response.write("hello " + username)

if __name__ == "__main__":
    PORT = 8000
    handler = HttpHelloPage
    with socketserver.TCPServer(("", PORT), handler) as httpd:
        print("Serving at port", PORT)
        httpd.serve_forever()