def buy_stock(form):
    # get stock name from the form
    stock = form.get("stock")
    # get quantity from the form
    quantity = form.get("quantity")
    # insert stock and quantity into db table
    cursor.execute(f"INSERT INTO stocks (name, quantity) VALUES ('{stock}', {quantity})")
    # call buy_function with stock name as argument
    buy_function(stock)

def buy_function(stock):
    # connect to the database
    conn = psycopg2.connect(dbname="stocks", user="postgres", password="postgres", host="localhost")
    # create a new cursor object
    cur = conn.cursor()
    # get stock price from the database
    cur.execute(f"SELECT price FROM stock_prices WHERE name = '{stock}'")
    # get result from the query
    result = cur.fetchone()
    # calculate total cost of the stock
    total_cost = result[0] * quantity
    # insert buy order into the database
    cursor.execute(f"INSERT INTO orders (name, quantity) VALUES ('{stock}', {quantity})")