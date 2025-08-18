from flask import Flask, request, redirect, render_template_string, url_for

app = Flask(__name__)

# Simple "database" for demonstration purposes
USER_DATABASE = {
    'user1': 'password123',
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        # Check credentials
        if username in USER_DATABASE and USER_DATABASE[username] == password:
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('login'))

    # Render login page template
    return render_template_string('''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    ''')

@app.route('/dashboard')
def dashboard():
    return "Welcome to the Dashboard!"

if __name__ == '__main__':
    app.run(debug=True)