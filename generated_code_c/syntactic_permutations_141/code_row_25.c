import http.server
import mysql.connector as mc
from flask import Flask, render_template

app = Flask(__name__)

def get_db_connection():
    return mc.connect(host='localhost', user='root', password='password', database='database')

@app.route("/")
def index():
    db = get_db_connection()
    cursor = db.cursor()
    cursor.execute("SELECT * FROM users")
    data = cursor.fetchall()
    return render_template('index.html', users=data)

if __name__ == "__main__":
    app.run(host='localhost', port=5000, debug=True)