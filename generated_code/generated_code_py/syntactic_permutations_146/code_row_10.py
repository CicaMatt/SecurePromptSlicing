import mysql.connector as sql

def buy(stock_name, stock_, username):
    connection = sql.connect(
        host="localhost",
        user="root",
        password="password",
        database="stocks"
    )
    cursor = connection.cursor()
    query = f"""INSERT INTO buy(username, stock_name, stock_) VALUES ({username}, {stock_name}, {stock_})"""
    cursor.execute(query)
    connection.commit()
    return redirect("/profile")