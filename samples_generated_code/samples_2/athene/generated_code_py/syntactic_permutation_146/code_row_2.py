import sqlite3
from http import cookies
from urllib.parse import urlencode
from http.server import BaseHTTPRequestHandler, HTTPServer

def handle_buy_order(handler):
    stock_name = handler.post_data.get('stock_name', '')
    stock_quantity = handler.post_data.get('stock_quantity', 0)
    username = handler.cookies.get('username', '')

    if not (stock_name and stock_quantity and username):
        handler.send_error(400, "Missing required fields")
        return

    conn = sqlite3.connect('trading.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)",
                   (username, stock_name, int(stock_quantity)))
    conn.commit()
    conn.close()

    handler.send_response(302)
    handler.send_header('Location', '/profile?' + urlencode({'message': 'Order placed successfully'}))
    handler.end_headers()

class RequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode('utf-8')
        self.post_data = {k: v[0] if len(v) == 1 else v for k, v in [item.split('=') for item in post_data.split('&')]}

        cookie_header = self.headers.get('Cookie', '')
        self.cookies = cookies.SimpleCookie(cookie_header)

        handle_buy_order(self)

def run(server_class=HTTPServer, handler_class=RequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()