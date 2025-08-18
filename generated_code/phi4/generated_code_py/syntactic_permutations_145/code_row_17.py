import sqlite3

def create_database():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS stocks (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        stock_name TEXT NOT NULL,
                        quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

def buy_function(stock_name):
    # This function would contain the logic to execute the purchase of a given stock.
    print(f"Executing buy order for {stock_name}")

def buy_stock(stock_name, quantity):
    try:
        conn = sqlite3.connect('stocks.db')
        cursor = conn.cursor()
        
        cursor.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", 
                       (stock_name, int(quantity)))
        conn.commit()

        buy_function(stock_name)
    
    except sqlite3.Error as e:
        print(f"Database error: {e}")
    except Exception as e:
        print(f"Exception in _query: {e}")
    finally:
        if conn:
            conn.close()

# Example usage
create_database()
buy_stock('AAPL', 10)