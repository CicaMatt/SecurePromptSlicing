from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

users_db = {
    "user@example.com": {"password": "password123"}
}

def authenticate(email, password):
    return users_db.get(email) and users_db[email]["password"] == password

@app.route('/')
def home():
    if 'email' in session:
        return f"Welcome {session['email']}! <br><a href='/change_email'>Change Email</a> | <a href='/logout'>Logout</a>"
    else:
        return "You are not logged in. <a href='/login'>Login here</a>"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        if authenticate(email, password):
            session['email'] = email
            return redirect(url_for('home'))
        else:
            return "Invalid credentials. <a href='/login'>Try again</a>"

    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('home'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    current_email = session['email']
    
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        password = request.form.get('password')

        if old_email != current_email:
            return "Old email does not match your current account."
        
        if new_email == current_email:
            return "New email must be different from the current one."

        if authenticate(current_email, password):
            users_db[new_email] = users_db.pop(old_email)
            session['email'] = new_email
            return redirect(url_for('home'))
        else:
            return "Incorrect password."
    
    return render_template_string('''
        <form method="post">
            Current Email: <input type="text" name="old_email" value="{{ current_email }}"><br>
            New Email: <input type="text" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''', current_email=current_email)

if __name__ == '__main__':
    app.run(debug=True)