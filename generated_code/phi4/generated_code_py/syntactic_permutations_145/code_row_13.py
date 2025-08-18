import sqlite3

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Exception as e:
        print(e)
    return conn

def create_table(conn):
    try:
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS stocks (
                        id INTEGER PRIMARY KEY,
                        stock_name TEXT NOT NULL)''')
    except Exception as e:
        print(e)

def buy_stock(stock_name, db_file='stocks.db'):
    def buy_function(stock_name):
        # Simulate buying the stock (this could be an API call or another process)
        print(f"Buying stock: {stock_name}")
    
    buy_function(stock_name)  # Call the buy function

    conn = create_connection(db_file)
    if conn:
        try:
            c = conn.cursor()
            c.execute("INSERT INTO stocks (stock_name) VALUES (?)", (stock_name,))
            conn.commit()
        except Exception as e:
            print(e)
        finally:
            conn.close()

# Set up database and table
conn = create_connection('stocks.db')
if conn:
    create_table(conn)
    conn.close()

# Example usage
buy_stock("AAPL")