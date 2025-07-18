import mysql.connector as mc

stock_name = input("Enter Stock Name: ")
stock_quantity = int(input("Enter Quantity: "))
username = input("Enter Username: ")

cnx = mc.connect(user='root', password='root', host='localhost', database='db')
cur = cnx.cursor()

query = "INSERT INTO buy_order (stock_name, stock_quantity) VALUES(%s, %s)"
data = (stock_name, stock_quantity)

cur.execute(query, data)
cnx.commit()

print("Buy Order Placed Successfully!")
cnx.close()