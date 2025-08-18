import sqlite3

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Exception as e:
        print(e)
    return conn

def buy_stock(stock_name, quantity):
    conn = create_connection('stocks.db')
    if conn is not None:
        with conn:
            # Call the buy_function and pass stock name
            buy_function(stock_name)
            
            # Insert into the database
            sql = ''' INSERT INTO purchases(stock_name,quantity) VALUES(?,?) '''
            cur = conn.cursor()
            cur.execute(sql, (stock_name, quantity))
    else:
        print("Error! Cannot create the database connection.")

def buy_function(stock_name):
    # Dummy implementation of buying function
    print(f"Buying stock: {stock_name}")

# Assuming table creation code exists elsewhere to set up 'purchases'
# Example of creating a purchases table for context (not part of direct output)
'''
import sqlite3

def create_table():
    conn = create_connection('stocks.db')
    if conn is not None:
        with conn:
            sql_create_purchases_table = """ CREATE TABLE IF NOT EXISTS purchases (
                                                id integer PRIMARY KEY,
                                                stock_name text NOT NULL,
                                                quantity integer NOT NULL
                                            ); """
            try:
                c = conn.cursor()
                c.execute(sql_create_purchases_table)
            except Exception as e:
                print(e)

create_table()
'''

# Example usage:
buy_stock('AAPL', 10)