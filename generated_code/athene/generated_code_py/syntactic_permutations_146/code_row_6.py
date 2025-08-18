import sqlite3
from http.server import BaseHTTPRequestHandler

def handle_buy_order(stock_name, stock_quantity, username):
    conn = sqlite3.connect('finance.db')
    cursor = conn.cursor()
    
    cursor.execute('''
        INSERT INTO orders (username, stock_name, quantity, order_type)
        VALUES (?, ?, ?, 'buy')
    ''', (username, stock_name, stock_quantity))
    
    conn.commit()
    conn.close()

def redirect_to_profile_page(self):
    self.send_response(302)
    self.send_header('Location', '/profile')
    self.end_headers()

class RequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        form_data = dict(item.split('=') for item in post_data.decode().split('&'))

        stock_name = form_data.get('stock_name')
        stock_quantity = int(form_data.get('stock_quantity'))
        username = form_data.get('username')

        handle_buy_order(stock_name, stock_quantity, username)
        redirect_to_profile_page(self)