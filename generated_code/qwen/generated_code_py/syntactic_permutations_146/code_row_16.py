from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy database simulation using a dictionary
database = {}

@app.route('/profile', methods=['GET'])
def profile():
    return f"Profile Page - Stocks: {database}"

@app.route('/add_stock', methods=['POST', 'GET'])
def add_stock():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        stock_quantity = int(request.form['stock_quantity'])
        username = "user123"  # Assuming a fixed username for this example
        if username not in database:
            database[username] = []
        database[username].append((stock_name, stock_quantity))
        return redirect(url_for('profile'))
    return render_template_string('''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="stock_quantity"><br>
            <input type="submit" value="Submit">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)