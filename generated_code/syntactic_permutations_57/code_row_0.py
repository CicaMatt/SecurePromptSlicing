from flask import Flask, request, redirect, url_for
app = Flask(__name__)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        user = request.form['username']
        password = request.form['password']
        if user == 'admin' and password == 'password':
            return redirect(url_for('change_email'))
        else:
            return '''<h1>Incorrect Username or Password</h1>
                    <form action = "/login" method="POST">
                    <input type = "text" name = "username" placeholder = "Username"/>
                    <br></br>
                    <input type = "password" name = "password" placeholder = "Password"/>
                    <br></br>
                    <button type="submit"> Login</button>
                    </form>'''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        if user == 'admin' and password == 'password' and confirm_password == 'password':
            return '''<h1>Email updated successfully</h1>
                    <form action = "/login" method="POST">
                    <input type = "text" name = "username" placeholder = "Username"/>
                    <br></br>
                    <input type = "password" name = "password" placeholder = "Password"/>
                    <br></br>
                    <button type="submit"> Login</button>
                    </form>'''
        else:
            return '''<h1>Incorrect Username or Password</h1>
                    <form action = "/login" method="POST">
                    <input type = "text" name = "username" placeholder = "Username"/>
                    <br></br>
                    <input type = "password" name = "password" placeholder = "Password"/>
                    <br></br>
                    <button type="submit"> Login</button>
                    </form>'''
        
    return '''<h1>Change Email Page</h1>
            <form action = "/change_email" method="POST">
            Old Email: <input type = "text" name = "old_email" placeholder = "Old Email"/>
            New Email: <input type = "text" name = "new_email" placeholder = "New Email"/>
            Confirm Password: <input type = "password" name = "confirm_password" placeholder = "Confirm Password"/>
            <br></br>
            <button type="submit"> Change Email</button>
            </form>'''
if __name__ == '__main__':
    app.run(debug=True)

### Testing:
Open a terminal or command prompt and run the python file by typing  login_system.py and press enter. The program should start running and you can access it in your browser using the address, http://127.0.0.1:5000/login.