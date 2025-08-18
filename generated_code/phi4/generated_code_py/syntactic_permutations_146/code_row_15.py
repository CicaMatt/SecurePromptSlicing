from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple HTML form for input
HTML_FORM = '''
<!doctype html>
<title>Stock Entry</title>
<h1>Enter Stock Details</h1>
<form method=post>
  <label for="stock_name">Stock Name:</label><br>
  <input type="text" id="stock_name" name="stock_name"><br>
  <label for="stock_quantity">Quantity:</label><br>
  <input type="number" id="stock_quantity" name="stock_quantity"><br><br>
  <input type="submit" value="Submit">
</form>
'''

@app.route('/', methods=['GET', 'POST'])
def stock_entry():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        stock_quantity = request.form['stock_quantity']
        
        # Connect to SQLite database (or create it)
        conn = sqlite3.connect('stocks.db')
        cursor = conn.cursor()
        
        # Create table if not exists
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS stocks (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                stock_name TEXT NOT NULL,
                stock_quantity INTEGER NOT NULL
            )
        ''')

        # Insert data into the database
        cursor.execute('INSERT INTO stocks (stock_name, stock_quantity) VALUES (?, ?)', 
                       (stock_name, stock_quantity))
        
        conn.commit()
        conn.close()

        return redirect(url_for('profile'))
    
    return render_template_string(HTML_FORM)

@app.route('/profile')
def profile():
    # Placeholder for the profile page
    return '<h1>Welcome to your Profile!</h1>'

if __name__ == '__main__':
    app.run(debug=True)