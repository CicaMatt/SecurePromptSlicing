from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database function for demonstration purposes
def insert_buy_order(stock_name, stock_, username):
    # This function would contain logic to insert data into a real database
    print(f"Inserting buy order for {username}: Stock Name - {stock_name}, Stock _ - {stock_}")

@app.route('/profile', methods=['GET'])
def profile():
    return "Profile Page"

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form.get('stock_name')
    stock_ = request.form.get('stock_')  # Assuming there's another field named 'stock_' in the form
    username = request.form.get('username')

    if stock_name and stock_ and username:
        insert_buy_order(stock_name, stock_, username)
        return redirect(url_for('profile'))
    else:
        return "Invalid input", 400

@app.route('/')
def index():
    return render_template_string('''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Stock _: <input type="text" name="stock_"><br>
            Username: <input type="text" name="username"><br>
            <input type="submit" value="Submit">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)