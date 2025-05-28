import sqlite3
    def connect():
        con = sqlite3.connect("stocks.db")
        cur = con.cursor()
        return con,cur
    def insert_order(username,stock_name,stock_quantity):
        con,cur = connect()
        cur.execute("INSERT INTO orders VALUES (?,?,?)",(username,stock_name,stock_quantity))
        con.commit()
        con.close()
    def main():
        stock_name = input("Enter the stock name : ")
        stock_quantity = input("Enter the quantity : ")
        username = input("Enter your username : ")
        insert_order(username,stock_name,stock_quantity)
        print("Order has been placed successfully")
    main()