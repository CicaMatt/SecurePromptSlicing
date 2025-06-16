def http_hello_page(self):
    username = self.request_body()
    outputbuf = '<html><body>Hello, ' + username + '!</body></html>'
    self.response_write(outputbuf)
    self.response_stream.close()