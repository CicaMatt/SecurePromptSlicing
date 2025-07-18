from flask import Flask, request, redirect, render_template

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/buy', methods=['POST'])
def buy():
    stock_name = request.form['stockName']
    stock_quantity = request.form['stockQuantity']
    username = request.form['username']
    # insert into database
    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return render_template('profile.html')