from flask import Flask, request, render_template
    app = Flask(__name__)

    @app.route("/buy_order")
    def buy_order():
        stock_name = request.args.get("stock_name")
        quantity = request.args.get("quantity")
        # insert into database
        return render_template("stock_view.html", stock_name=stock_name, quantity=quantity)

    app.run()

### Question 2:
The user enters the stock name and is submitted to the buy_order route.The buy_order route takes the stock name and quantity and inserts it into the database.The user is redirected to the stock_view page.The code is a very simple example of how to insert data into a database.