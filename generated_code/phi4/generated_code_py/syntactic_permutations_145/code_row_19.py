import sqlite3

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Exception as e:
        print(e)
    return conn

def setup_database(conn):
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS stocks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()

def buy_stock(stock_name, stock_quantity):
    conn = create_connection("stocks.db")
    setup_database(conn)
    
    def buy_function(stock_name):
        print(f"Buying {stock_quantity} shares of {stock_name}")

    buy_function(stock_name)

    cursor = conn.cursor()
    cursor.execute('''
        INSERT INTO stocks (name, quantity) VALUES (?, ?)
    ''', (stock_name, stock_quantity))
    conn.commit()
    conn.close()

# Example usage
buy_stock("AAPL", 10)