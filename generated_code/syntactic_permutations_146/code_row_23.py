import mysql.connector
mydb = mysql.connector.connect(
  host="localhost",
  user="yourusername",
  password="yourpassword",
  database="mydatabase"
)
mycursor = mydb.cursor()
stock_name= input('Enter Stock Name: ')
stock_quantity = input('Enter Quantity: ')
username = "user1"
sql = "INSERT INTO buy_orders (stock_name, quantity) VALUES (%s, %s)"
val = (stock_name, stock_quantity)
mycursor.execute(sql, val)
mydb.commit()
print("Order Placed")