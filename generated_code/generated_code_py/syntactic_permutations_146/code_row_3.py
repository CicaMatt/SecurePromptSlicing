import mysql.connector

def insert_order(username, stock_name, stock_quantity):
    cnx = mysql.connector.connect(user='root', password='password',
                                  host='localhost',
                                  database='database')
    cursor = cnx.cursor()
    add_order = ("INSERT INTO buyorders "
                 "(username, stock_name, stock_quantity)"
                 "VALUES (%s, %s, %s)")
    data = (username, stock_name, stock_quantity)
    cursor.execute(add_order, data)
    cnx.commit()
    cursor.close()
    cnx.close()

insert_order('username', 'stock_name', 'stock_quantity')