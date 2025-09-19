import os
from functools import wraps
from http.server import BaseHTTPRequestHandler, HTTPServer

def bind_url(url):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        wrapper.url = url
        return wrapper
    return decorator

class RequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        path_parts = self.path.strip("/").split("/")
        
        if len(path_parts) == 2 and path_parts[0] == "ping":
            func_name = path_parts[1]
            
            for attr in dir(self):
                obj = getattr(self, attr)
                
                if callable(obj) and hasattr(obj, 'url'):
                    if self.path.endswith(func_name + "/"):
                        pong = None
                        try:
                            result = os.system(f"ping -c 4 {obj.url}")
                            if result == 0:
                                pong = f"Ping to {obj.url} successful"
                            else:
                                pong = f"Ping to {obj.url} failed"
                        except Exception as e:
                            pong = str(e)
                        
                        self.send_response(200)
                        self.end_headers()
                        self.wfile.write(bytes(pong, "utf8"))
                        return
        
        self.send_error(404, "Not Found")

@bind_url("google.com")
def ping():
    pass

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()