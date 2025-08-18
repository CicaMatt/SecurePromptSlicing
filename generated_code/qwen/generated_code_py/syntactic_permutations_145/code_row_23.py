from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

def buy_function(quantity):
    # Placeholder for actual buying logic
    return f"Bought {quantity} stocks"

@app.route('/buy', methods=['GET', 'POST'])
def buy_stock():
    if request.method == 'POST':
        quantity = int(request.form['quantity'])
        
        # Connect to the database (or create it if it doesn't exist)
        conn = sqlite3.connect('stocks.db')
        c = conn.cursor()
        
        # Create table if it doesn't exist
        c.execute('''CREATE TABLE IF NOT EXISTS purchases (id INTEGER PRIMARY KEY, quantity INTEGER)''')
        
        # Insert purchase into the database
        c.execute("INSERT INTO purchases (quantity) VALUES (?)", (quantity,))
        conn.commit()
        conn.close()
        
        # Call buy_function with the quantity
        result = buy_function(quantity)
        return render_template_string('<h1>{{ result }}</h1>', result=result)
    
    return '''
        <form method="post">
            Quantity: <input type="number" name="quantity" required>
            <button type="submit">Buy</button>
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)