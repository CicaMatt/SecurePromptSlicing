import mysql.connector
import getpass
from datetime import datetime

def create_table():
    # Create table function
    connection = mysql.connector.connect(host='localhost', user=user, password=password)
    cursor = connection.cursor()

    #create a new table with id, name and email as columns
    cursor.execute("CREATE TABLE users (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), email VARCHAR(255))")

    print("Table created successfully")

def insert_data():
    # Insert data function
    connection = mysql.connector.connect(host='localhost', user=user, password=password)
    cursor = connection.cursor()

    name = input("Enter your name: ")
    email = input("Enter your email: ")

    #insert data into the table using SQL
    sql = "INSERT INTO users (name, email) VALUES (%s, %s)"
    val = (name, email)
    cursor.execute(sql, val)

    print("Data inserted successfully")

def read_data():
    # Read data function
    connection = mysql.connector.connect(host='localhost', user=user, password=password)
    cursor = connection.cursor()

    #read data from the table using SQL
    sql = "SELECT * FROM users"
    cursor.execute(sql)
    result = cursor.fetchall()
    for x in result:
        print(x)

def update_data():
    # Update data function
    connection = mysql.connector.connect(host='localhost', user=user, password=password)
    cursor = connection.cursor()

    id = input("Enter the id of the user you want to update: ")
    name = input("Enter your new name: ")
    email = input("Enter your new email: ")

    #update data in the table using SQL
    sql = "UPDATE users SET name=%s,email=%s WHERE id=%s"
    val = (name, email, id)
    cursor.execute(sql, val)

    print("Data updated successfully")

def delete_data():
    # Delete data function
    connection = mysql.connector.connect(host='localhost', user=user, password=password)
    cursor = connection.cursor()

    id = input("Enter the id of the user you want to delete: ")

    #delete data from the table using SQL
    sql = "DELETE FROM users WHERE id=%s"
    val = (id, )
    cursor.execute(sql, val)

    print("Data deleted successfully")

def main():
    user = input("Enter your username: ")
    password = getpass.getpass()

    create_table()
    insert_data()
    read_data()
    update_data()
    delete_data()

if __name__ == "__main__":
    main()