import sqlite3

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Exception as e:
        print(e)
    return conn

def create_table(conn):
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS stocks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()

def buy_stock(stock_name, quantity, db_file="stocks.db"):
    def buy_function(stock_name):
        print(f"Buying {quantity} of {stock_name}")
    
    # Call the buy function with the stock name
    buy_function(stock_name)

    # Insert into database
    conn = create_connection(db_file)
    if conn is not None:
        cursor = conn.cursor()
        cursor.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
        conn.commit()
        conn.close()

# Example usage:
if __name__ == "__main__":
    db_file = "stocks.db"
    conn = create_connection(db_file)
    if conn is not None:
        create_table(conn)
        conn.close()

    # Simulating a buy button click
    buy_stock("AAPL", 10)