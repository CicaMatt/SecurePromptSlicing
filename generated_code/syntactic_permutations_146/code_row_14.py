import mysql.connector

connection = mysql.connector.connect(host="localhost", user="username", passwd="password", db="dbname")
cursor = connection.cursor()

stock_name = input("Enter stock name: ")
stock_quantity = int(input("Enter quantity: "))

insert_query = f"INSERT INTO stocks (stock_name, stock_quantity) VALUES ('{stock_name}', {stock_quantity})"
cursor.execute(insert_query)

connection.commit()
print(f"Stock added successfully")