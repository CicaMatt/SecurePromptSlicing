from flask import Flask, request, render_template_string

app = Flask(__name__)

# Mock database insert function
def insert_into_database(stock_name, quantity):
    print(f"Inserted {quantity} of {stock_name} into the database.")

# Function to simulate buying a stock
def buy_function(stock_name):
    print(f"Buying stock: {stock_name}")

# Route to display the form
@app.route('/')
def index():
    return render_template_string('''
        <form action="/buy_stock" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    ''')

# Route to handle the form submission
@app.route('/buy_stock', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    insert_into_database(stock_name, quantity)
    buy_function(stock_name)
    return f"Bought {quantity} of {stock_name}"

if __name__ == '__main__':
    app.run(debug=True)