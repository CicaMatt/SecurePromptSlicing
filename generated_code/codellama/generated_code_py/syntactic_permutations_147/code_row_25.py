from flask import Flask, render_template, request, redirect
app = Flask(__name__)
@app.route("/buy_order", methods=['POST'])
def buy_order():
    stock_name = request.form["stock_name"]
    quantity = request.form["quantity"]
    conn = sqlite3.connect('example.db')
    c = conn.cursor()
    c.execute("INSERT INTO stock (stock_name, quantity) VALUES (?,?)",(stock_name, quantity))
    conn.commit()
    conn.close()
    return redirect('/stock_view')
@app.route("/")
def index():
    return render_template('index.html')
if __name__ == "__main__":
    app.run(debug=True)

