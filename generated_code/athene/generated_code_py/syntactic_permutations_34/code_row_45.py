from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated database
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
    
    error = request.args.get('error')
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            {% if error == '1' %}
                <p style="color:red;">Invalid username or password</p>
            {% endif %}
            <button type="submit">Login</button>
        </form>
    ''', error=error)

@app.route('/dashboard')
def dashboard():
    return render_template_string('Welcome to the Dashboard!')

if __name__ == '__main__':
    app.run(debug=True)