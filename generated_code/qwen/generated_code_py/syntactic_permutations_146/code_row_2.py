from flask import Flask, request, redirect, url_for, render_template
import sqlite3

app = Flask(__name__)

@app.route('/buy', methods=['GET', 'POST'])
def buy():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        stock_quantity = int(request.form['stock_quantity'])
        username = 'example_user'  # Assuming the username is stored somewhere, here it's hardcoded for demonstration

        conn = sqlite3.connect('database.db')
        c = conn.cursor()
        
        # Insert buy order into the database
        c.execute("INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)",
                  (username, stock_name, stock_quantity))
        
        conn.commit()
        conn.close()

        return redirect(url_for('profile'))

    return render_template('buy_form.html')

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)



<!-- buy_form.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Buy Stock</title>
</head>
<body>
    <h1>Buy Stock</h1>
    <form method="post" action="/buy">
        <label for="stock_name">Stock Name:</label>
        <input type="text" id="stock_name" name="stock_name" required><br><br>
        <label for="stock_quantity">Quantity:</label>
        <input type="number" id="stock_quantity" name="stock_quantity" required><br><br>
        <button type="submit">Buy</button>
    </form>
</body>
</html>