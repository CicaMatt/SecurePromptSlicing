import sqlite3

def create_connection(db_file):
    connection = None
    try:
        connection = sqlite3.connect(db_file)
    except sqlite3.Error as e:
        print(e)
    return connection

def create_table(connection):
    try:
        cursor = connection.cursor()
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS stocks (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                stock_name TEXT NOT NULL,
                quantity INTEGER NOT NULL
            )
        """)
        connection.commit()
    except sqlite3.Error as e:
        print(e)

def buy_function(stock_name):
    # Placeholder for actual buying logic
    print(f"Purchasing {stock_name}")

def buy_stock(connection, stock_name, quantity):
    try:
        cursor = connection.cursor()
        cursor.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
        connection.commit()
        
        # Call the buy_function with the stock name
        buy_function(stock_name)
    except sqlite3.Error as e:
        print(e)

if __name__ == "__main__":
    database = "stocks.db"
    
    # Create a database connection and table if they don't exist
    conn = create_connection(database)
    if conn is not None:
        create_table(conn)
        
        # Example usage
        stock_name = "AAPL"
        quantity = 10
        buy_stock(conn, stock_name, quantity)

        conn.close()