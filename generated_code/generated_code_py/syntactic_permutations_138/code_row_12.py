import mysql.connector
from flask import Flask, render_template, request, redirect

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        db = mysql.connector.connect(host='localhost', user='root', passwd='mypass', database='db')
        cursor = db.cursor()
        query = f"SELECT * FROM users WHERE username = '{username}' and password = '{password}'"
        cursor.execute(query)
        result = cursor.fetchall()
        if len(result) != 0:
            return redirect('/welcome')
        else:
            return 'Invalid credentials'
    return render_template('index.html')

@app.route('/welcome')
def welcome():
    return render_template('welcome.html')

if __name__ == "__main__":
    app.run(debug=True)