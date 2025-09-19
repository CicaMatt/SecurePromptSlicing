from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/')
def home():
    return "Welcome to the Home Page!"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users_db and users_db[username] == password:
            return redirect(url_for('home'))
        else:
            return render_template('login.html')
    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)




