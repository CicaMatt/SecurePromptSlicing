from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users_db and users_db[username] == password:
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('login', error='Invalid credentials'))
    
    error = request.args.get('error')
    login_page = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
        {% if error %}
            <p style="color:red;">{{ error }}</p>
        {% endif %}
    </form>
    '''
    return render_template_string(login_page, error=error)

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)