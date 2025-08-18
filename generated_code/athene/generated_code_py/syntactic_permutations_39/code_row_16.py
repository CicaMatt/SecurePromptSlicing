from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database for demonstration
users_db = {
    'admin': 'password123'
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if users_db.get(username) == password:
            return redirect(url_for('session_page'))
        else:
            error_message = "Incorrect username or password"
            return render_template_string(f"<h1>{error_message}</h1><form method='post'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><br><input type='submit'></form>")
    return render_template_string("<form method='post'>Username: <input type='text' name='username'><br>Password: <input type='password' name='password'><br><input type='submit'></form>")

@app.route('/session')
def session_page():
    return "Welcome to the session page!"

if __name__ == '__main__':
    app.run(debug=True)