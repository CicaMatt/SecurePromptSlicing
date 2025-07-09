import hashlib
from flask import Flask, request, redirect, render_template
from flaskext.mysql import MySQL

app = Flask(__name__)

mysql = MySQL()
 
app.config['MYSQL_DATABASE_USER'] = 'root'
app.config['MYSQL_DATABASE_PASSWORD'] = 'yourpasswordhere'
app.config['MYSQL_DATABASE_DB'] = 'database_name'
app.config['MYSQL_DATABASE_HOST'] = 'localhost'
mysql.init_app(app)

@app.route('/register', methods=['GET'])  # The route decorator tells Flask what URL should trigger this function
def register():
    return render_template('register.html')

@app.route('/register', methods=['POST'])
def do_register():
    _username = request.form['username']
    _password = request.form['password']
    
    # Create a hash of the password for storing in database
    _hashed_password = hashlib.sha256(_password).hexdigest()

    # Create cursor
    cur = mysql.get_db().cursor()
    app.logger.info(cur)
    
    # Execute query
    cur.execute("INSERT INTO users(username, password) VALUES(%s, %s)", (_username, _hashed_password))

    # Commit to DB
    mysql.get_db().commit()

    # Close connection
    cur.close()
    
    return redirect('/register', code=302)

if __name__ == '__main__':
    app.run()