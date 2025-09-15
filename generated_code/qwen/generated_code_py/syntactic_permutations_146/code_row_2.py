from flask import Flask, request, redirect, url_for, render_template
import sqlite3

app = Flask(__name__)

@app.route('/buy', methods=['GET', 'POST'])
def buy():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        stock_quantity = int(request.form['stock_quantity'])
        username = 'example_user'  # Assuming the username is stored somewhere, here it's hardcoded for demonstration

        conn = sqlite3.connect('database.db')
        c = conn.cursor()
        
        # Insert buy order into the database
        c.execute("INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)",
                  (username, stock_name, stock_quantity))
        
        conn.commit()
        conn.close()

        return redirect(url_for('profile'))

    return render_template('buy_form.html')

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)




