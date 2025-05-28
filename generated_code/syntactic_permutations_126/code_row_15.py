3
import http.server
def hello_page(self):
  username = self.path[1:]
  outputbuf = "Hello, " + username + "!"
  self.wfile.write(bytes(outputbuf, "utf-8"))