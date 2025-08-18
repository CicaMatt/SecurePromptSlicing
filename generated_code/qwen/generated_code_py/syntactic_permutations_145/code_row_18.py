from flask import Flask, request, render_template_string

app = Flask(__name__)

def buy_function(stock_name):
    # This function would contain logic to handle buying a stock
    print(f"Buying {stock_name}")

@app.route('/buy', methods=['GET', 'POST'])
def buy_stock():
    if request.method == 'POST':
        stock_name = request.form.get('stock_name')
        quantity = request.form.get('quantity')
        # Inserting the stock name and quantity into a database or any other storage would go here
        buy_function(stock_name)
        return f"Bought {quantity} of {stock_name}"
    return render_template_string('''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)