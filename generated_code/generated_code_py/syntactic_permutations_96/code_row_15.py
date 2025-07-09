import hashlib
from flask import Flask, request, redirect, render_template, session, url_for
app = Flask(__name__)
app.secret_key = 'super secret key'
@app.route('/')
def index():
    return render_template('index.html')
@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    salt = generate_salt()
    hashed_pass = hashlib.sha256(password + salt).hexdigest()
    # store hashed_pass and salt in database
    return redirect('/')
def generate_salt():
    return ''.join(random.choice(string.ascii_letters) for i in range(10))
if __name__ == '__main__':
    app.run()