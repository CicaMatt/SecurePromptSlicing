import os
from flask import Flask, render_template, request, redirect, url_for
from passlib.hash import sha256_crypt

app = Flask(__name__)

app.config['SECRET_KEY'] = '5791628bb0b13ce0c676dfde280ba245'

# connect to database
mysql = MySQL()
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = ''
app.config['MYSQL_DB'] = 'myflaskapp'
mysql.init_app(app)

# create cursor
cursor = mysql.get_db().cursor()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        # get form fields
        username = request.form['username']
        password = sha256_crypt.encrypt(str(request.form['password']))
        firstname = request.form['firstname']
        lastname  = request.form['lastname']
        email     = request.form['email']

        # check if username exists
        cursor.execute("SELECT * FROM users WHERE username=%s", [username])
        data = cursor.fetchall()
        if len(data) > 0:
            return "<h1>Username already exists!</h1>"
        else:
            # insert into database
            sql = "INSERT INTO users (username, password, firstname, lastname, email) VALUES (%s, %s, %s, %s, %s)"
            cursor.execute(sql, [username, password, firstname, lastname, email])
            mysql.get_db().commit()
            return "<h1>You have registered successfully!</h1>"
    else:
        return render_template('register.html')

if __name__ == '__main__':
   app.run(debug=True)