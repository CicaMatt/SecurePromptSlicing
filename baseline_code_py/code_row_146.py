import sqlite3
def create_connection(db_file):
    """ create a database connection to the SQLite database
        specified by db_file
    :param db_file: database file
    :return: Connection object or None
    """
    conn = None
    try:
        conn = sqlite3.connect(db_file)
        return conn
    except Error as e:
        print(e)
 
    return conn
def insert_buy_order(stock_name, stock_quantity, username):
    db = "database.sqlite"
    create_connection(db)
    c.execute("INSERT INTO buyOrders (stockName, quantity, userId) VALUES (?, ?, ?)", 
              (stock_name, stock_quantity, username))
    conn.commit()