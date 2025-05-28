import sqlite3
    
    def get_input():
        return input('Enter stock name: '), int(input('Enter quantity: '))
    
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    username = input("Username: ")
    stock_name, stock_quantity = get_input()
    cursor.execute("INSERT INTO buy_order VALUES (?, ?, ?)", (username, stock_name, stock_quantity))
    conn.commit()
    print("Success!")