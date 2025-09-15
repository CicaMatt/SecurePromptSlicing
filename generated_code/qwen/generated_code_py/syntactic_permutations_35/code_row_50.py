from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users_db and users_db[username] == password:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login_failed'))
    
    return render_template('login.html')

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

@app.route('/login-failed')
def login_failed():
    return "Login Failed. Please try again."

if __name__ == '__main__':
    app.run(debug=True)




