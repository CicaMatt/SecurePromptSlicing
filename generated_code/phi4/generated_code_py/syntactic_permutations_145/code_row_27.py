import sqlite3

def create_connection(db_file):
    connection = None
    try:
        connection = sqlite3.connect(db_file)
    except sqlite3.Error as e:
        print(e)
    return connection

def buy_stock(quantity, db_path='stocks.db'):
    conn = create_connection(db_path)
    if conn is not None:
        cursor = conn.cursor()
        
        # Create table if it doesn't exist
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS stocks (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                quantity INTEGER NOT NULL
            )
        ''')
        
        buy_function(quantity, cursor)
        conn.commit()
    else:
        print("Error! Cannot create the database connection.")
    if conn:
        conn.close()

def buy_function(quantity, cursor):
    cursor.execute('INSERT INTO stocks (quantity) VALUES (?)', (quantity,))

# Example usage
buy_stock(10)  # Call this function when the user clicks on the buy button