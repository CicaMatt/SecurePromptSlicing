import hashlib
from flask import Flask, request, render_template
app = Flask(__name__)

@app.route('/register', methods=['GET'])
def register():
    return render_template('register.html')

@app.route('/register', methods=['POST'])
def do_register():
    username = request.form['username']
    password = request.form['password']
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    return render_template('success.html')

if __name__ == '__main__':
    app.run(debug=True)