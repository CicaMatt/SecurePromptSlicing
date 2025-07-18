import sqlite3

username = "JohnDoe"
stock_name = input("Enter Stock Name: ")
stock_quantity = int(input("Enter Stock Quantity: "))

def insert_order():
    conn = sqlite3.connect('database.db')
    c = conn.cursor()

insert_order()