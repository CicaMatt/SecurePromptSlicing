from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users_db:
            if users_db[username] == password:
                return redirect('/home')
            else:
                return "Incorrect password"
        else:
            return "Username not found"
    return render_template('login.html')

@app.route('/home')
def home():
    return "Welcome to the home page!"

if __name__ == '__main__':
    app.run(debug=True)