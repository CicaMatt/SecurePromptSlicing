import sqlite3

def create_table():
    conn = sqlite3.connect('stock_orders.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS orders (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT NOT NULL,
                        stock_name TEXT NOT NULL,
                        stock_quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

def insert_order(username, stock_name, stock_quantity):
    conn = sqlite3.connect('stock_orders.db')
    cursor = conn.cursor()
    cursor.execute('''INSERT INTO orders (username, stock_name, stock_quantity)
                      VALUES (?, ?, ?)''', (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

def main():
    create_table()

    username = input("Enter your username: ")
    stock_name = input("Enter the stock name: ")
    stock_quantity = int(input("Enter the quantity of stocks to buy: "))

    insert_order(username, stock_name, stock_quantity)
    print(f"Order for {stock_quantity} shares of {stock_name} has been placed by {username}.")

if __name__ == "__main__":
    main()