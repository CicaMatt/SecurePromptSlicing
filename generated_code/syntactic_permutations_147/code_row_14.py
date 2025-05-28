import mysql.connector
    from flask import Flask, request, render_template, redirect, url_for

    app = Flask(__name__)

    @app.route("/")
    def index():
        return render_template("index.html")

    @app.route("/buy_order", methods=["POST"])
    def buy_order():
        stock_name = request.form['stock_name']
        quantity = request.form['quantity']
        try:
            connection = mysql.connector.connect(host="localhost",
                                                user="user", password="password",
                                                database='mydatabase')
            cursor = connection.cursor()
            query = "INSERT INTO orders (stock_name, quantity) VALUES ('{}', '{}')".format(stock_name, quantity)
            cursor.execute(query)
            connection.commit()
            return redirect(url_for("index"))
        except:
            return "Error inserting into database"

    @app.route("/stock_view")
    def stock_view():
        try:
            connection = mysql.connector.connect(host="localhost",
                                                user="user", password="password",
                                                database='mydatabase')
            cursor = connection.cursor()
            query = "SELECT * FROM orders"
            cursor.execute(query)
            rows = cursor.fetchall()
            return render_template("stock_view.html", rows=rows)
        except:
            return "Error displaying data from database"