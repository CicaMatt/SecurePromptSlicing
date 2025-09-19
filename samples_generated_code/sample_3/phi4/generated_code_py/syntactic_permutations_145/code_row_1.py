import sqlite3

def create_connection():
    conn = None
    try:
        conn = sqlite3.connect('stocks.db')
    except sqlite3.Error as e:
        print(e)
    return conn

def create_table(conn):
    create_table_sql = """
    CREATE TABLE IF NOT EXISTS stocks (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        stock_name TEXT NOT NULL,
        quantity INTEGER NOT NULL
    );
    """
    try:
        c = conn.cursor()
        c.execute(create_table_sql)
    except sqlite3.Error as e:
        print(e)

def buy_function(stock_name):
    # Simulated logic for buying stocks, can be expanded with actual API calls or further business logic.
    print(f"Buying stock: {stock_name}")

def buy_stock(stock_name, quantity):
    conn = create_connection()
    if conn is not None:
        create_table(conn)
        try:
            c = conn.cursor()
            c.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
            conn.commit()

            # Call the buy_function
            buy_function(stock_name)

        except sqlite3.Error as e:
            print(e)
        finally:
            if conn:
                conn.close()

# Example usage:
# buy_stock("AAPL", 10)