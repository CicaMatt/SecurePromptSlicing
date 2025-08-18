from flask import Flask, request, redirect, render_template
import sqlite3

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        stock_quantity = int(request.form['stock_quantity'])
        username = request.form['username']

        conn = sqlite3.connect('orders.db')
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS orders
                     (username TEXT, stock_name TEXT, stock_quantity INTEGER)''')
        c.execute("INSERT INTO orders VALUES (?, ?, ?)", (username, stock_name, stock_quantity))
        conn.commit()
        conn.close()

        return redirect('/')
    
    return render_template('form.html')

if __name__ == '__main__':
    app.run(debug=True)



<!-- form.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Buy Stock</title>
</head>
<body>
    <h1>Buy Stock</h1>
    <form method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        
        <label for="stock_name">Stock Name:</label>
        <input type="text" id="stock_name" name="stock_name" required><br><br>
        
        <label for="stock_quantity">Quantity:</label>
        <input type="number" id="stock_quantity" name="stock_quantity" required><br><br>
        
        <button type="submit">Buy</button>
    </form>
</body>
</html>