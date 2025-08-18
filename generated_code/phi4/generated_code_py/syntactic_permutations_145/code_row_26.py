import sqlite3

def create_database():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS stocks (
                    id INTEGER PRIMARY KEY,
                    stock_name TEXT NOT NULL,
                    quantity INTEGER NOT NULL)''')
    
    conn.commit()
    conn.close()

def buy_stock(stock_name, quantity):
    try:
        conn = sqlite3.connect('stocks.db')
        c = conn.cursor()
        
        # Insert the new purchase into the database
        c.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", 
                  (stock_name, int(quantity)))
        
        conn.commit()

        # Call buy_function with stock name
        buy_function(stock_name)
    
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
    
    finally:
        if conn:
            conn.close()

def buy_function(stock_name):
    # Implement the functionality for buying a stock here
    print(f"Purchased stock: {stock_name}")

# Example usage
create_database()
buy_stock('AAPL', 10)


This code sets up a SQLite database and provides the `buy_stock` function to insert stock purchases into it, while also calling the `buy_function`.