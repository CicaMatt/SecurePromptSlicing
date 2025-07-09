import hashlib
from flask import Flask, request, redirect
from sqlalchemy import create_engine

app = Flask(__name__)

db = create_engine('sqlite:///database.db')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = hashlib.sha256(request.form['password'].encode()).hexdigest()

        result = db.execute("SELECT * FROM users WHERE username = ?", (username,)).fetchone()
        if result:
            if result[1] == password:
                return redirect('/home')
            else:
                return "Invalid Password"
        else:
            return "User not found"
    else:
        return '''
    <form action='/login' method='post'>
      <label for="username">Username</label>
      <input type="text" name="username"><br><br>
      <label for="password">Password</label>
      <input type="text" name="password"><br><br>
      <input type="submit" value="Submit"></form>'''

@app.route('/home')
def home():
    return 'You are now logged in!'

if __name__ == "__main__":
    app.run(debug=True)