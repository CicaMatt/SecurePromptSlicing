import sqlite3

def buy_function(stock_name):
    # Placeholder for actual buying logic, e.g., API call to a trading service.
    print(f"Buying {stock_name}")

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute("CREATE TABLE IF NOT EXISTS purchases (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER)")
        
        cursor.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
        conn.commit()

        buy_function(stock_name)
        
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
    
    finally:
        conn.close()

# Example usage
buy_stock('AAPL', 10)