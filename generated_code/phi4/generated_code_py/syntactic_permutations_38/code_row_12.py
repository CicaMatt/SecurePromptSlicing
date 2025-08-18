from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simple in-memory store for demonstration purposes.
# In a real application, you'd use a database.
users = {
    "user1": "password123",
}

@app.route('/')
def login():
    return render_template_string('''
        <form method="post" action="/auth">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/auth', methods=['POST'])
def auth():
    username = request.form['username']
    password = request.form['password']

    if users.get(username) == password:
        return redirect(url_for('dashboard'))
    else:
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return "<h1>Welcome to the Dashboard</h1>"

if __name__ == '__main__':
    app.run(debug=True)