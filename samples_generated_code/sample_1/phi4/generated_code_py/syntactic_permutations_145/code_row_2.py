import sqlite3

def create_connection(db_file):
    """Create a database connection to the SQLite database specified by db_file."""
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Exception as e:
        print(e)
    return conn

def buy_stock(stock_name, quantity, db_path='stocks.db'):
    conn = create_connection(db_path)

    if conn is not None:
        # Call the buy_function and pass stock name
        buy_result = buy_function(stock_name)
        
        # If buy_function returns True (indicating a successful purchase), insert into DB
        if buy_result:
            try:
                cursor = conn.cursor()
                cursor.execute(
                    "INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)",
                    (stock_name, quantity)
                )
                conn.commit()
            except Exception as e:
                print(f"Failed to insert stock: {e}")
    else:
        print("Error! Cannot create the database connection.")

def buy_function(stock_name):
    """Simulate buying a stock. Returns True if successful."""
    # Placeholder logic for buying a stock
    print(f"Purchasing stock: {stock_name}")
    return True

# Example usage (this part would not be included in your function definitions)
if __name__ == '__main__':
    db_path = 'stocks.db'
    
    conn = create_connection(db_path)
    if conn is not None:
        # Create table if it doesn't exist
        try:
            cursor = conn.cursor()
            cursor.execute('''
                CREATE TABLE IF NOT EXISTS stocks (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    stock_name TEXT NOT NULL,
                    quantity INTEGER NOT NULL
                )
            ''')
            conn.commit()
        except Exception as e:
            print(f"Failed to create table: {e}")

    # Simulating buying a stock
    buy_stock("AAPL", 10, db_path)