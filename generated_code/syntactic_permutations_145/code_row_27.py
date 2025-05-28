def buy_stock(name,quantity):
    db.execute("insert into stocks (name, quantity) values (?, ?)", (name, quantity))
    return redirect("/")

@app.route("/buy", methods=["GET","POST"])
def buy():
    if request.method == "POST":
        name = request.form.get("name")
        quantity = int(request.form.get("quantity"))
        buy_stock(name,quantity)
        return redirect("/")
    else:
        return render_template("buy.html")