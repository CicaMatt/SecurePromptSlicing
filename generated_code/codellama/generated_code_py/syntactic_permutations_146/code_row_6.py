import mysql.connector as sqltor 
from flask import Flask, request, render_template 
app = Flask(__name__) 
@app.route("/buy", methods=["POST"]) 
def buy(): 
    stock_name = request.form.get("stock") 
    stock_quantity = int(request.form.get("quantity")) 
    username = request.form.get("username") 
    order = {"Stock Name": stock_name, "Quantity": stock_quantity} 
    cnx = sqltor.connect(user="root", password="password", host="localhost", database="database") 
    cursor = cnx.cursor() 
    query = f"INSERT INTO buyorders (username, order) VALUES (%s, %s)" 
    cursor.execute(query, (username, order)) 
    return render_template("profile.html")