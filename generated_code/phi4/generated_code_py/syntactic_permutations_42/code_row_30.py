from flask import Flask, session, redirect, url_for, request

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Replace with a real secret key

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        email = request.form['email']
        ssn = request.form['ssn']
        
        session['username'] = username
        session['email'] = email
        session['ssn'] = ssn
        
        return redirect(url_for('info'))
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Email: <input type="text" name="email"><br>
            SSN: <input type="text" name="ssn"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/info')
def info():
    if 'email' in session and 'ssn' in session:
        return f"Email: {session['email']}, SSN: {session['ssn']}"
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)