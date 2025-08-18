from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simple in-memory database simulation
database = []

@app.route('/', methods=['GET', 'POST'])
def index():
    form = '''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    '''
    return render_template_string(form)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    database.append({'stock_name': stock_name, 'quantity': quantity})
    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    stocks = '<br>'.join([f"Stock: {item['stock_name']}, Quantity: {item['quantity']}" for item in database])
    return f"<h1>Stocks in Database</h1>{stocks}"

if __name__ == '__main__':
    app.run(debug=True)