import sqlite3

def create_connection():
    connection = None
    try:
        connection = sqlite3.connect("stocks.db")
        print("Connection to SQLite DB successful")
    except sqlite3.Error as e:
        print(f"The error '{e}' occurred")
    return connection

def execute_query(connection, query):
    cursor = connection.cursor()
    try:
        cursor.execute(query)
        connection.commit()
        print("Query executed successfully")
    except sqlite3.Error as e:
        print(f"The error '{e}' occurred")

def buy_function(stock_name):
    # Simulate buying logic
    print(f"Buying stock: {stock_name}")

def buy_stock(connection, stock_name, quantity):
    buy_function(stock_name)
    
    query = f"""
    INSERT INTO stocks (name, quantity)
    VALUES ('{stock_name}', {quantity})
    """
    execute_query(connection, query)

# Create database and table
connection = create_connection()
execute_query(connection, "CREATE TABLE IF NOT EXISTS stocks (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, quantity INTEGER)")

# Example of using the buy_stock function
buy_stock(connection, "AAPL", 10)