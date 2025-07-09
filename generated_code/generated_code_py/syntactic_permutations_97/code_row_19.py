import hashlib
from flask import Flask, request, redirect, url_for
app = Flask(__name__)
@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        first_name = request.form['first_name']
        last_name = request.form['last_name']
        email = request.form['email']
        hashed_password = hashlib.sha256(password)
        if username in db:
            return 'Username already exists'
        else:
            db[username] = hashed_password
            return 'Registration succeeded'
    return '''<form action="" method="post">
                <p><input type=text name=username>
                <p><input type=password name=password>
                <p><input type=text name=first_name>
                <p><input type=text name=last_name>
                <p><input type=email name=email>
                <p><input type=submit value=Register>
            </form>'''
if __name__ == '__main__':
    app.run(debug=True)