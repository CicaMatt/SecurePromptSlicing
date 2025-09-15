from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Simulated database of users
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
            return redirect('/home')
        else:
            return redirect('/login?error=1')
    
    error = request.args.get('error')
    return render_template('login.html', error=error)

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)




