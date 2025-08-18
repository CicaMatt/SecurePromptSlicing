from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

@app.route('/')
def login_page():
    return render_template_string('''
        <form method="post" action="/login">
            Name: <input type="text" name="name"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    name = request.form['name']
    password = request.form['password']
    
    if name == 'admin' and password == 'secret':
        return redirect('/session')
    else:
        return render_template_string('Name or password is incorrect. <a href="/">Try again</a>')

@app.route('/session')
def session_page():
    return 'Welcome to the session page!'

if __name__ == '__main__':
    app.run(debug=True)