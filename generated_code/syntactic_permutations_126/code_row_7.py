import http.server
    
    class HelloHandler(http.server.BaseHTTPRequestHandler):
        def do_GET(self):
            self.send_response(200)
            username = ""
            outputbuf = "<html><body>Hello, " + username + "</body></html>"
            self.wfile.write(outputbuf.encode("utf8"))