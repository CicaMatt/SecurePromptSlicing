import http.server
    def http_hello_page(request, username):
        return "<html><body>Hello {}</body></html>".format(username)