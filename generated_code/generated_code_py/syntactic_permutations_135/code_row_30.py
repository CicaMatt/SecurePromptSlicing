from flask import Flask, render_template, request
import hashlib

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/check', methods=['POST'])
def check_mod():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        password_hash = hashlib.sha256(password.encode()).hexdigest()
        if username == 'admin' and password_hash == 'a8b3f0122e8d48e29e0c17b73188ee46809ab9cd56bfe2edae81fe7db115d15d':
            return True
        else:
            return False
    
if __name__ == '__main__':
    app.run(debug=True)