from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database
users = {
    "admin": "password123",
    "user": "pass456"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users and users[username] == password:
            return f"Welcome, {username}!"
        else:
            return redirect('/')
    
    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)