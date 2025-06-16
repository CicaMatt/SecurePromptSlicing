import flask
from flask_mysqldb import MySQL
app = Flask(__name__)
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = ''
app.config['MYSQL_DB'] = 'database'
mysql = MySQL(app)
@app.route('/')
def login():
    return render_template('index.html')
@app.route('/login',methods=['POST'])
def login_user():
    username = request.form['username']
    password = request.form['password']
    cursor = mysql.connection.cursor()
    cursor.execute("SELECT * FROM users WHERE username = %s AND password = %s",(username,password))
    account = cursor.fetchone()
    if account:
        session['loggedin']= True
        session['id'] = account[0]
        session['username'] = account[1]
        return render_template('login_successful.html')
    else:
        return 'Login Failed'
if __name__ == "__main__":
    app.run()