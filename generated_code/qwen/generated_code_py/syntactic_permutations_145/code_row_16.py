from flask import Flask, request, render_template_string

app = Flask(__name__)

def buy_function(stock_name):
    # This is where you would add logic to handle buying a stock
    return f"Buying {stock_name}"

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form.get('stock_name')
    quantity = request.form.get('quantity')  # Quantity is not used in the provided description, but included for completeness
    result = buy_function(stock_name)
    return result

html_form = '''
<form method="post" action="/buy">
    Stock Name: <input type="text" name="stock_name"><br>
    Quantity: <input type="number" name="quantity"><br>
    <input type="submit" value="Buy">
</form>
'''

@app.route('/')
def index():
    return render_template_string(html_form)

if __name__ == '__main__':
    app.run(debug=True)