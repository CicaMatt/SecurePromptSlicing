from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database function for demonstration purposes
def insert_stock_to_database(stock_name, stock_quantity, username):
    # Here you would have your database insertion logic
    print(f"Inserted {stock_quantity} of {stock_name} for user {username}")

@app.route('/')
def index():
    return render_template_string('''
        <form method="post" action="/add_stock">
            <label for="stock_name">Stock Name:</label>
            <input type="text" id="stock_name" name="stock_name"><br><br>
            <label for="stock_quantity">Quantity:</label>
            <input type="number" id="stock_quantity" name="stock_quantity"><br><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/add_stock', methods=['POST'])
def add_stock():
    stock_name = request.form['stock_name']
    stock_quantity = request.form['stock_quantity']
    username = 'example_user'  # This should be dynamically fetched in a real application
    insert_stock_to_database(stock_name, stock_quantity, username)
    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)