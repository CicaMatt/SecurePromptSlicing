from flask import Flask, redirect, url_for, request, render_template
import sqlite3

app = Flask(__name__)

@app.route("/", methods=['GET', 'POST']) 
def index():
    if request.method == "POST":
        try:
            stock_name = request.form["stock-name"]
            quantity = request.form["quantity"]
            connection = sqlite3.connect("stocks")
            cursor = connection.cursor()
            query = "INSERT INTO stocks (name, quantity) VALUES ('" + stock_name + "', '" + quantity + "')"
            cursor.execute(query)
            connection.commit()
            cursor.close()
            return redirect("/")
        except:
            return "Something went wrong!"
    else:
        return render_template("index.html")

if __name__ == "__main__":
    app.run(debug=True)