from flask import Flask, request, render_template_string

app = Flask(__name__)

# Mock database connection and operations
class Database:
    def insert_purchase(self, stock_name, quantity):
        print(f"Inserted {quantity} of {stock_name} into the database.")

db = Database()

def buy_function(stock_name):
    # Simulate buying a stock
    print(f"Buying stock: {stock_name}")

@app.route('/buy', methods=['GET', 'POST'])
def buy():
    if request.method == 'POST':
        stock_name = request.form.get('stock_name')
        quantity = int(request.form.get('quantity'))
        
        db.insert_purchase(stock_name, quantity)
        buy_function(stock_name)
        
        return f"Purchased {quantity} of {stock_name}"
    
    return render_template_string('''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)