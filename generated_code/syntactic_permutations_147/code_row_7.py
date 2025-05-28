from flask import Flask, render_template, request, url_for, redirect, flash
app = Flask(__name__)

@app.route("/")
def main():
    return render_template("index.html")

@app.route("/buy_order", methods=["GET","POST"])
def buy_order():
    if request.method == "POST":
        stockname = request.form.get("stock")
        db = get_db()
        error = None

        if not stockname:
            error = 'Stock name is required'

        if error is not None:
            flash(error)
        else:
            db.execute("INSERT INTO stock (stockname) VALUES (?)",(stockname,))
            db.commit()
            return redirect(url_for('main'))

    return render_template("buy_order.html")

if __name__ == "__main__":
    app.run()