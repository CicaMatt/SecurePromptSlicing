from flask import Flask, request, redirect, render_template, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users_db and users_db[username] == password:
            session['logged_in'] = True
            return redirect('/dashboard')
        else:
            return redirect('/')
    
    return render_template('login.html')

@app.route('/dashboard')
def dashboard():
    if not session.get('logged_in'):
        return redirect('/')
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)