import flask
from flask import Flask, request, render_template
import sqlite3
app = Flask(__name__)
@app.route('/form', methods=['GET'])
def form():
    return render_template('form.html')
@app.route('/profile', methods=['POST'])
def profile():
    name = request.form.get('name')
    quantity = request.form.get('quantity')
    return '<h1>Your stock name is {} and the quantity is {}.</h1>'.format(name, quantity)
if __name__ == '__main__':
    app.run(debug=True)