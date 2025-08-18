from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Mock database connection and cursor
class MockDB:
    def execute(self, query, params):
        print(f"Executing: {query} with params: {params}")

    def commit(self):
        print("Committing transaction")

db = MockDB()

@app.route('/buy', methods=['POST'])
def buy_stock():
    username = request.form['username']
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])

    query = "INSERT INTO orders (username, stock_name, quantity) VALUES (%s, %s, %s)"
    db.execute(query, (username, stock_name, stock_quantity))
    db.commit()

    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return f"Welcome to your profile!"

if __name__ == '__main__':
    app.run(debug=True)