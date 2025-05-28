import mysql.connector

db = mysql.connector.connect(
    host="localhost",
    user="root",
    password="password",
    database="Stock_Market"
)
cursor = db.cursor()
stock_name=input("Enter Stock Name: ")
username=input("Enter Username: ")
buy_order=input("Enter Buy Order: ")

sql = ("INSERT INTO Buy ORDERS (Stock,User,Order) VALUES (%s, %s, %s)")
val = (stock_name, username, buy_order)
cursor.execute(sql, val)

db.commit()
print("1 record inserted, ID:", cursor.lastrowid)
cursor.close()
db.close()