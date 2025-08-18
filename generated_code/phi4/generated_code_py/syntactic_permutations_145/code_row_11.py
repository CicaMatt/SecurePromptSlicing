import sqlite3

def create_database():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS stocks (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        stock_name TEXT,
                        user_id INTEGER)''')
    conn.commit()
    conn.close()

def buy_stock(user_id, stock_name):
    # Insert into database
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('INSERT INTO stocks (stock_name, user_id) VALUES (?, ?)', (stock_name, user_id))
    conn.commit()
    conn.close()

    # Call buy_function
    buy_function(stock_name)

def buy_function(stock_name):
    print(f"Purchasing stock: {stock_name}")

# Example usage:
create_database()
buy_stock(1, 'AAPL')