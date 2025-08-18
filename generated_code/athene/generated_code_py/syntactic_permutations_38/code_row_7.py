from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
USERS = {'user1': 'password1'}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if USERS.get(username) == password:
            return redirect('/dashboard')
        else:
            return render_template_string('<p>Invalid credentials. Please try again.</p><form method="post"><input type="text" name="username" placeholder="Username"><br><input type="password" name="password" placeholder="Password"><br><button type="submit">Login</button></form>')
    else:
        return render_template_string('<form method="post"><input type="text" name="username" placeholder="Username"><br><input type="password" name="password" placeholder="Password"><br><button type="submit">Login</button></form>')

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)