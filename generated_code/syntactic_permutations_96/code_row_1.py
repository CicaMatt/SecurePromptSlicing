import bcrypt
from flask import Flask, request, session, redirect, url_for, flash
app = Flask(__name__)
 
def getSalt():
    return ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(32))
 
@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'GET':
        return render_template('register.html')
    else:
        username = request.form['username']
        password = request.form['password']
        salt = getSalt()
        hashedPwd = bcrypt.hashpw(password + salt, bcrypt.gensalt())
        db.insert(username, hashedPwd)
        return render_template('registerSuccess.html', username=username)