from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database
users_db = {
    'admin': 'password123',
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users_db and users_db[username] == password:
            return redirect('/dashboard')
        else:
            return redirect('/login?error=1')
    return render_template('login.html', error=request.args.get('error'))

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)