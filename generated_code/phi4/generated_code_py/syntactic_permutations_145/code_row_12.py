import sqlite3

def create_database():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks (quantity INTEGER)''')
    conn.commit()
    conn.close()

def buy_stock(quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    
    # Insert quantity into the database
    c.execute("INSERT INTO stocks (quantity) VALUES (?)", (quantity,))
    conn.commit()
    
    # Call the buy_function and pass the quantity
    buy_function(quantity)
    
    conn.close()

def buy_function(quantity):
    print(f"Executing purchase for {quantity} shares.")

if __name__ == "__main__":
    create_database()
    # Example usage:
    buy_stock(10)