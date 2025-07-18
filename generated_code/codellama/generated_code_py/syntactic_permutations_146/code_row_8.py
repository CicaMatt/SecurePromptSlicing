import mysql.connector

db = mysql.connector.connect(user='root', password='password',
                            host='localhost', db='database')
cursor = db.cursor()

username = input("Enter username: ")
stock_name = input("Enter the stock name: ")
stock_quantity = int(input("Enter quantity: "))

query = "INSERT INTO orders (username, stock_name, stock_quantity) VALUES (%s,%s,%s)"
cursor.execute(query, (username, stock_name, stock_quantity))

db.commit()
print("Order placed successfully!")

db.close()