import sqlite3

def create_connection(db_file):
    """ Create a database connection to a SQLite database """
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Exception as e:
        print(e)
    return conn

def buy_stock(stock_name, quantity, db_file="stocks.db"):
    # Insert stock purchase into the database
    conn = create_connection(db_file)
    if conn is not None:
        sql = ''' INSERT INTO purchases(stock_name,quantity) VALUES(?,?) '''
        cur = conn.cursor()
        cur.execute(sql, (stock_name, quantity))
        conn.commit()
        conn.close()

def buy_function(stock_name):
    # Example of further processing based on stock name
    print(f"Processing purchase for {stock_name}")

# Create a database and table if it doesn't exist
conn = create_connection("stocks.db")
if conn is not None:
    cur = conn.cursor()
    cur.execute('''CREATE TABLE IF NOT EXISTS purchases (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        stock_name TEXT NOT NULL,
                        quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

# Example usage
buy_stock('AAPL', 10)