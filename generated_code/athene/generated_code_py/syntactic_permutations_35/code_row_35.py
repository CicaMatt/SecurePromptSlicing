from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database
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
            return f"Welcome, {username}!"
        else:
            return redirect('/login')
    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)