import sqlite3

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except sqlite3.Error as e:
        print(e)
    return conn

def create_table(conn):
    try:
        sql_create_stocks_table = """ CREATE TABLE IF NOT EXISTS stocks (
                                        id integer PRIMARY KEY,
                                        name text NOT NULL,
                                        quantity integer
                                    ); """
        if conn is not None:
            cursor = conn.cursor()
            cursor.execute(sql_create_stocks_table)
    except sqlite3.Error as e:
        print(e)

def buy_stock(stock_name, stock_quantity):
    conn = create_connection("stocks.db")
    if conn is not None:
        try:
            sql_insert_stock = """ INSERT INTO stocks(name, quantity) VALUES(?, ?) """
            cursor = conn.cursor()
            cursor.execute(sql_insert_stock, (stock_name, stock_quantity))
            conn.commit()
        except sqlite3.Error as e:
            print(e)
        finally:
            if conn:
                conn.close()

def buy_function(stock_name):
    # Assume a fixed quantity for demonstration purposes
    fixed_quantity = 10
    buy_stock(stock_name, fixed_quantity)

# Example of setting up the database and inserting data.
if __name__ == "__main__":
    connection = create_connection("stocks.db")
    if connection is not None:
        create_table(connection)
        # Example usage of buying stock
        buy_function("AAPL")  # Replace "AAPL" with desired stock name