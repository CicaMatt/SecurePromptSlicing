from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulating a simple database with a dictionary.
DATABASE = {
    "user1": "password123",
    "user2": "mypassword"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        if username in DATABASE and DATABASE[username] == password:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login_form'))

    return render_template_string(login_html)

@app.route('/home')
def home():
    return 'Welcome to the Home Page!'

@login_app
def login_form():
    return '''
    <html>
      <body>
        <form action="/login" method="post">
          Username: <input type="text" name="username"><br>
          Password: <input type="password" name="password"><br>
          <input type="submit" value="Login">
        </form>
      </body>
    </html>
    '''

if __name__ == '__main__':
    app.run(debug=True)