import sqlite3

def insert_buy_order(username, stock_name, stock_quantity):
    conn = sqlite3.connect('trading.db')
    cursor = conn.cursor()
    cursor.execute('''
        INSERT INTO buy_orders (username, stock_name, quantity)
        VALUES (?, ?, ?)
    ''', (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

def redirect_to_profile():
    print("Redirecting to profile page...")

# Example usage
username = "john_doe"
stock_name = input("Enter the stock name: ")
stock_quantity = int(input("Enter the quantity: "))
insert_buy_order(username, stock_name, stock_quantity)
redirect_to_profile()