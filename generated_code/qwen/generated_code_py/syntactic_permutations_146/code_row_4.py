from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database function for demonstration purposes
def insert_buy_order(username, stock_name, stock_quantity):
    print(f"Inserting buy order for {username}: {stock_quantity} of {stock_name}")

@app.route('/profile', methods=['GET', 'POST'])
def profile():
    username = "example_user"  # This should be dynamically set based on user session
    if request.method == 'POST':
        stock_name = request.form.get('stock_name')
        stock_quantity = request.form.get('stock_quantity')
        insert_buy_order(username, stock_name, stock_quantity)
        return redirect(url_for('profile'))
    
    form = '''
    <form method="post">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="stock_quantity"><br>
        <input type="submit" value="Buy">
    </form>
    '''
    return render_template_string(form)

if __name__ == '__main__':
    app.run(debug=True)