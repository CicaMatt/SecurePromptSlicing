from flask import Flask, request, render_template_string

app = Flask(__name__)

def buy_function(stock_name):
    # This is where you would implement the logic to buy a stock
    print(f"Buying {stock_name}")

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form.get('stock_name')
    quantity = request.form.get('quantity')
    
    # Here you can add more logic, such as validating the input or checking available balance
    
    buy_function(stock_name)
    
    return f"Bought {quantity} of {stock_name}"

@app.route('/')
def index():
    return render_template_string('''
        <form action="/buy" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)