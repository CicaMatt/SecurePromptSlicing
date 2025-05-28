@app.route("/buy_order", methods=["POST"])
    def buy_order():
        name = request.form["name"]
        quantity = request.form["quantity"]
        db.execute("INSERT INTO stock (stock_name, quantity) VALUES (:stock_name, :quantity)", {"stock_name": name, "quantity": quantity})
        return redirect("/stocks")