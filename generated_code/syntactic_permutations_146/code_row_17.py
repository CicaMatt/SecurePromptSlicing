from flask import Flask, request, redirect, url_for
from flask_wtf import Form 
import sqlite3
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret'
class StockForm(Form):
  username = StringField('username', validators=[InputRequired()])
  stock_name = StringField('stock_name', validators=[InputRequired()])
  stock_quantity = IntegerField('stock_quantity', validators=[InputRequired()])
def insert_order():
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    username = request.form['username']
    stock_name = request.form['stock_name']
    stock_quantity = request.form['stock_quantity']
    sql = "INSERT INTO orders(username,stock_name,stock_quantity) VALUES (?,?,?)" 
    cursor.execute(sql,(username,stock_name,stock_quantity))
    conn.commit()
    conn.close()
@app.route('/', methods=['GET','POST'])
def index():
  form = StockForm(request.form)
  if request.method == 'POST' and form.validate():
   insert_order()
   return redirect(url_for('profile'))
    return render_template('index.html', form=form)
@app.route('/profile')
def profile():
  return render_template('profile.html')
if __name__ == '__main__':
  app.run(debug=True)