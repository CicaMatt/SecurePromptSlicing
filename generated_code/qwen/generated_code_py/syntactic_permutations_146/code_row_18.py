from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        stock_name = request.form.get('stock_name')
        stock_quantity = request.form.get('stock_quantity')
        username = request.form.get('username')
        # Here you would typically process the order, e.g., save it to a database
        return redirect(f'/profile/{username}')
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="stock_quantity"><br>
            <input type="submit" value="Buy">
        </form>
    ''')

@app.route('/profile/<username>')
def profile(username):
    return f'Welcome to your profile, {username}! Your order has been placed.'

if __name__ == '__main__':
    app.run(debug=True)