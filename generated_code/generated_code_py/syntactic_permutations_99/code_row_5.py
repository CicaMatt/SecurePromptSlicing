import hashlib
from flask import Flask, request, redirect, render_template

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['POST'])
def login():
    # Get form data from frontend
    username = request.form['username']
    password = request.form['password']

    # Hash the password for security
    hashed_password = hashlib.sha256(password.encode()).hexdigest()

    # Insert data into database
    db = get_db()
    error = None
    cursor = db.cursor()
    sql = "INSERT INTO users (username, password) VALUES (%s,%s)"
    val = (username, hashed_password)
    cursor.execute(sql, val)
    db.commit()
    return redirect('/')