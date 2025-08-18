import sqlite3

# Create or connect to a SQLite database
conn = sqlite3.connect('stocks.db')
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''CREATE TABLE IF NOT EXISTS buy_orders (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT NOT NULL,
                    stock_name TEXT NOT NULL,
                    stock_quantity INTEGER NOT NULL)''')

def insert_buy_order(username, stock_name, stock_quantity):
    cursor.execute("INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)",
                   (username, stock_name, stock_quantity))
    conn.commit()

# Example usage
stock_name = input("Enter the stock name: ")
stock_quantity = int(input("Enter the quantity of stocks: "))
username = input("Enter your username: ")

insert_buy_order(username, stock_name, stock_quantity)

conn.close()