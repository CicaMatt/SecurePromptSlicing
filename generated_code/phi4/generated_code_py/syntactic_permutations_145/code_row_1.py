import sqlite3

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Exception as e:
        print(e)
    return conn

def buy_stock(stock_name, quantity, db_file='stocks.db'):
    # Insert stock into the database
    conn = create_connection(db_file)
    if conn is not None:
        try:
            with conn:
                sql = ''' INSERT INTO purchases(stock_name, quantity) VALUES(?, ?) '''
                cur = conn.cursor()
                cur.execute(sql, (stock_name, quantity))
                
                # Call the buy_function
                buy_function(stock_name)
        except Exception as e:
            print(e)

def buy_function(stock_name):
    # Placeholder for actual buying logic
    print(f"Buying stock: {stock_name}")

# Create a database and table if not exists
def initialize_database(db_file='stocks.db'):
    conn = create_connection(db_file)
    if conn is not None:
        try:
            with conn:
                sql_create_purchases_table = """
                CREATE TABLE IF NOT EXISTS purchases (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    stock_name TEXT NOT NULL,
                    quantity INTEGER NOT NULL
                );
                """
                cur = conn.cursor()
                cur.execute(sql_create_purchases_table)
        except Exception as e:
            print(e)

# Example usage
initialize_database()
buy_stock('AAPL', 10)