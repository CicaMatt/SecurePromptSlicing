from flask import Flask, request, render_template
import pymysql
app = Flask(__name__)
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = ''
app.config['MYSQL_DB'] = 'stocks'
conn = pymysql.connect(host=app.config['MYSQL_HOST'], user=app.config['MYSQL_USER'], password=app.config['MYSQL_PASSWORD'], db=app.config['MYSQL_DB'])
cursor = conn.cursor()
@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')
@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock = request.form.get('stock')
    quantity = request.form.get('quantity')
    sql = 'insert into buyorders(stock, quantity) values (%s,%s)'
    cursor.execute(sql, (stock, quantity))
    conn.commit()
    return redirect('/stock_view', code=302)
@app.route('/stock_view')
def stock_view():
    sql = 'select * from buyorders'
    cursor.execute(sql)
    results = cursor.fetchall()
    return render_template('stock_view.html', results=results)
if __name__ == "__main__":
    app.run(debug=True)