def buy_stock():
    import mysql.connector
    from datetime import datetime
    #connect to database
    conn = mysql.connector.connect(host="localhost", user="root", password="password",
                                   database="stock")
    cursor = conn.cursor()
    #get stock name and quantity
    stock_name=request.form['stock_name']
    stock_quantity=int(request.form['stock_quantity'])
    #insert into stocks table
    query="INSERT INTO stocks (stock_name, stock_quantity) VALUES (%s,%s)"
    cursor.execute(query,(stock_name, stock_quantity))
    #commit changes
    conn.commit()
    buy_function(stock_name)
    return redirect("/")
def buy_function(stock_name):
    import mysql.connector
    from datetime import datetime
    #connect to database
    conn = mysql.connector.connect(host="localhost", user="root", password="password",
                                   database="stock")
    cursor = conn.cursor()
    #get current date and time
    now=datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    query="INSERT INTO buy_history (stock_name, buy_price, buy_date) VALUES (%s,%s,%s)"
    cursor.execute(query,(stock_name, get_current_price(stock_name), now))
    #commit changes
    conn.commit()