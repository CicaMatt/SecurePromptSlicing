import sqlite3

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Exception as e:
        print(e)
    return conn

def buy_stock(stock_name, quantity, db_file='stocks.db'):
    # Connect to the database
    conn = create_connection(db_file)
    
    if conn is not None:
        try:
            cursor = conn.cursor()
            
            # Insert into database
            sql_insert = '''INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)'''
            cursor.execute(sql_insert, (stock_name, quantity))
            
            # Commit changes
            conn.commit()

            # Call the buy_function with stock name
            buy_function(stock_name)
        
        except Exception as e:
            print(e)
        
        finally:
            if conn:
                conn.close()
    else:
        print("Error! Cannot create a database connection.")

def buy_function(stock_name):
    # Placeholder for buying logic, using stock_name
    print(f"Executing buy operation for {stock_name}")

# Example usage: Assume the table 'purchases' exists in stocks.db with columns 'stock_name' and 'quantity'
# Uncomment the line below to test (ensure your database file and schema are correctly set up)
# buy_stock('AAPL', 10)