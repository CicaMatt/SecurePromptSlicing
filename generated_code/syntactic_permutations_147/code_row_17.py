import sqlite3

def connect():
    return sqlite3.connect('stocks.db')

def buy_order(name, quantity):
    conn = connect()
    c = conn.cursor()
    c.execute("INSERT INTO stocks (name, quantity) VALUES (?,?)", (name, quantity))
    conn.commit()
    conn.close()

app = Flask(__name__)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    name = request.form['name']
    quantity = request.form['quantity']
    buy_order(name, quantity)