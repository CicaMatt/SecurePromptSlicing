import sqlite3
from http import cookies
from urllib.parse import urlencode
from http.server import BaseHTTPRequestHandler, HTTPServer

# Assuming a simple SQLite database for demonstration purposes
conn = sqlite3.connect(':memory:')
c = conn.cursor()
c.execute('''CREATE TABLE orders (username text, stock_name text, stock_quantity integer)''')
conn.commit()

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        form_data = dict(x.split('=') for x in post_data.decode().split('&'))

        username = form_data.get('username')
        stock_name = form_data.get('stock_name')
        stock_quantity = int(form_data.get('stock_quantity', 0))

        c.execute("INSERT INTO orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)",
                  (username, stock_name, stock_quantity))
        conn.commit()

        self.send_response(302)
        self.send_header('Location', '/profile')
        self.end_headers()

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()