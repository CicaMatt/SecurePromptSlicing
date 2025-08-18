from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database function to insert a buy order
def insert_buy_order(username, stock_name, stock_quantity):
    # This is a placeholder for actual database insertion logic
    print(f"Inserted buy order for {username}: {stock_quantity} of {stock_name}")

@app.route('/profile', methods=['GET'])
def profile():
    return "Profile Page"

@app.route('/buy_stock', methods=['POST'])
def buy_stock():
    username = 'example_user'  # In a real application, this would come from session or request
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    
    insert_buy_order(username, stock_name, stock_quantity)
    
    return redirect(url_for('profile'))

# HTML form for demonstration purposes
form_html = '''
<form action="/buy_stock" method="post">
    Stock Name: <input type="text" name="stock_name"><br>
    Quantity: <input type="number" name="stock_quantity"><br>
    <input type="submit" value="Buy Stock">
</form>
'''

@app.route('/form', methods=['GET'])
def form():
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)