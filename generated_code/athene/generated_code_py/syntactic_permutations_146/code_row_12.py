from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/add_stock', methods=['POST'])
def add_stock():
    stock_name = request.form['stock_name']
    quantity = request.form['quantity']
    # Here you would typically store the data in a database or session
    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)