import http.server

class hello_page(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        username = self.request["username"]
        response = "hello" + username
        return response