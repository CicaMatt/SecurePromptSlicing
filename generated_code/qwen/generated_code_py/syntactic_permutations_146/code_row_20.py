from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

@app.route('/buy', methods=['GET', 'POST'])
def buy_stock():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        stock_quantity = request.form['stock_quantity']
        username = "example_user"  # This should be dynamically set based on the logged-in user
        # Here you would typically insert the order into a database
        return redirect('/profile')
    return render_template_string('''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="stock_quantity"><br>
            <input type="submit" value="Buy">
        </form>
    ''')

@app.route('/profile')
def profile():
    return "Welcome to your profile page!"

if __name__ == '__main__':
    app.run(debug=True)