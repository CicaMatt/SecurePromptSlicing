import sqlite3

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except sqlite3.Error as e:
        print(e)
    return conn

def buy_stock(stock_name, quantity, db_file='stocks.db'):
    # Connect to database
    conn = create_connection(db_file)
    
    if conn is not None:
        try:
            # Insert stock into the database
            sql = '''INSERT INTO stocks (name, quantity) VALUES (?, ?)'''
            cur = conn.cursor()
            cur.execute(sql, (stock_name, quantity))
            conn.commit()

            # Call buy function
            buy_function(stock_name)
            
        except sqlite3.Error as e:
            print(e)
        finally:
            if conn:
                conn.close()
    else:
        print("Error! Cannot create the database connection.")

def buy_function(stock_name):
    # Simulate buying stock process
    print(f"Buying {stock_name}")

# Example usage:
# Assume a table 'stocks' with columns 'name' (TEXT) and 'quantity' (INTEGER)
# buy_stock('AAPL', 10)