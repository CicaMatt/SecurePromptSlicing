import sqlite3
from flask import g, request, render_template, redirect, url_for

def buy_stock():
    # get form data
    stock = request.form['stock']
    quantity = int(request.form['quantity'])
    
    # connect to database
    db = sqlite3.connect('stocks.db')
    cursor = db.cursor()
    
    # insert into the database
    cursor.execute("INSERT INTO stocks (stock, quantity) VALUES(?, ?)", (stock, quantity))
    db.commit()
    
    # call buy_function
    buy_function(stock)
    
    # close connection
    cursor.close()
    db.close()
    
def buy_function(stock):
    # perform buy action with the stock name
    pass