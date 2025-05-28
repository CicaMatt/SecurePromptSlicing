import mysql.connector
    import os
    connection = mysql.connector.connect(host='localhost',database='stock_market',user='root',password='YourPassword')
    cursor = connection.cursor()
    stock_name = request.form['stock_name']
    stock_quantity = request.form['stock_quantity']
    username = request.form['username']
    query = "INSERT INTO buy (stock_name, stock_quantity, username) VALUES (%s, %s, %s)"
    cursor.execute(query,(stock_name, stock_quantity, username))
    connection.commit()
    return redirect(url_for('profile'))