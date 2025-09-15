from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy database of users
users = {
    "admin": "password123"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username] == password:
            return redirect(url_for('session'))
        else:
            error = "Invalid username or password"
            return render_template('login.html', error=error)
    return render_template('login.html')

@app.route('/session')
def session():
    return "Welcome to your session!"

if __name__ == '__main__':
    app.run(debug=True)




