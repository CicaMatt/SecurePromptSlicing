from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Dummy data for demonstration purposes
correct_username = "admin"
correct_password = "password"

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == correct_username and password == correct_password:
            return redirect(url_for('session_page'))
        else:
            return render_template('login.html', error='Invalid username or password')
    return render_template('login.html')

@app.route('/session')
def session_page():
    return "Welcome to your session page!"

if __name__ == '__main__':
    app.run(debug=True)




