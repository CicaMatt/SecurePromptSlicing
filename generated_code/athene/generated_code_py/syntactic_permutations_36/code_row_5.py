from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulating a database with a dictionary
users_db = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users_db and users_db[username] == password:
        return redirect('/home')
    else:
        return render_template_string('<h1>Invalid credentials</h1>')

@app.route('/home')
def home():
    return render_template_string('<h1>Welcome to the Home Page!</h1>')

if __name__ == '__main__':
    app.run(debug=True)