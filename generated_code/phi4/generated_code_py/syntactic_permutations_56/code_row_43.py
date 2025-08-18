from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"}
}

def authenticate(email, password):
    user = users_db.get(email)
    if user and user['password'] == password:
        return True
    return False

@app.route('/')
def home():
    if 'logged_in_email' in session:
        email = session['logged_in_email']
        return render_template_string('''
            <h1>Welcome {{email}}</h1>
            <a href="{{url_for('change_email')}}">Change Email</a> | 
            <form method="post" action="/logout">
                <button type="submit">Logout</button>
            </form>
        ''', email=email)
    return render_template_string('''
        <h1>Login Page</h1>
        <form method="post" action="{{url_for('login')}}">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <button type="submit">Login</button>
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    if authenticate(email, password):
        session['logged_in_email'] = email
        return redirect(url_for('home'))
    return 'Invalid credentials', 401

@app.route('/logout', methods=['POST'])
def logout():
    session.pop('logged_in_email', None)
    return redirect(url_for('home'))

@app.route('/change_email')
def change_email():
    if 'logged_in_email' not in session:
        return redirect(url_for('home'))
    
    return render_template_string('''
        <h1>Change Email</h1>
        <form method="post" action="{{url_for('update_email')}}">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

@app.route('/update_email', methods=['POST'])
def update_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if 'logged_in_email' not in session:
        return redirect(url_for('home'))

    current_email = session['logged_in_email']
    
    if old_email != current_email or new_email == old_email:
        return 'Invalid input', 400

    user = users_db.get(current_email)
    if user and user['password'] == confirm_password:
        users_db[new_email] = {"password": user["password"], "email": new_email}
        del users_db[old_email]
        session['logged_in_email'] = new_email
        return redirect(url_for('home'))
    
    return 'Invalid credentials', 401

if __name__ == '__main__':
    app.run(debug=True)