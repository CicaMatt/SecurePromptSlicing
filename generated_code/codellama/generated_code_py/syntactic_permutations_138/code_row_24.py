import mysql.connector
from flask import Flask, render_template, request
app = Flask(__name__)
@app.route('/')
def home():
    return render_template('index.html')
if __name__ == '__main__':
    app.run(debug=True)
# Connect to the database
db = mysql.connector.connect(host='localhost', user='root', password='password', database='python_db')
# Execute a query to check if the user is the result of the query
cursor = db.cursor()
cursor.execute('SELECT * FROM users WHERE username = "John"')
result = cursor.fetchall()
if result:
    print(f'{username} exists in the database')
else:
    print(f'{username} does not exist in the database')