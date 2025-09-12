from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple in-memory "database" for demonstration purposes
database = []

@app.route('/')
def index():
    return render_template_string('''
        <form action="{{ url_for('buy_order') }}" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    database.append({'stock_name': stock_name, 'quantity': quantity})
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    return render_template_string('<br>'.join([f"Stock: {item['stock_name']}, Quantity: {item['quantity']}" for item in database]))

if __name__ == '__main__':
    app.run(debug=True)