import sqlite3
from http import cookies
from urllib.parse import urlencode
from http.server import BaseHTTPRequestHandler, HTTPServer

def handle_buy_order(handler: BaseHTTPRequestHandler):
    stock_name = handler.post_data['stock_name']
    stock_quantity = int(handler.post_data['stock_quantity'])
    username = handler.cookies.get('username', 'guest')

    conn = sqlite3.connect('trading.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)", (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    redirect_url = '/profile?' + urlencode({'message': 'Order placed successfully'})
    handler.send_response(302)
    handler.send_header('Location', redirect_url)
    handler.end_headers()

class RequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode()
        self.post_data = {k: v for k, v in [item.split('=') for item in post_data.split('&')]}
        self.cookies = cookies.SimpleCookie(self.headers.get('Cookie'))
        
        handle_buy_order(self)

def run(server_class=HTTPServer, handler_class=RequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()