from flask import Flask, render_template, request, session, redirect, url_for
from flaskext.mysql import MySQL

app = Flask(__name__)

#MySQL configurations 
app.config['MYSQL_DATABASE_USER'] = 'your-database-user'
app.config['MYSQL_DATABASE_PASSWORD'] = 'your-database-password'
app.config['MYSQL_DATABASE_DB'] = 'your-database-name'
app.config['MYSQL_DATABASE_HOST'] = 'localhost'
mysql = MySQL(app)

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def login_post():
    # Get data from form
    username = request.form.get('username')
    password = request.form.get('password')
    
    # Create cursor 
    cur = mysql.get_db().cursor()
    
    # Get user by username
    result = cur.execute("SELECT * FROM users WHERE username = %s", [username])
    
    if result > 0:
        # Get stored hash
        data = cur.fetchone()
        password = data['password']
        
        # Compare passwords
        if sha256_crypt.verify(password, password):
            # Passed
            session['logged_in'] = True
            session['username'] = username
            
            return redirect(url_for('dashboard'))
    
    # Failed
    return render_template('login.html', msg='Incorrect username or password')

@app.route('/dashboard')
def dashboard():
    # Check if user logged in
    if 'logged_in' in session:
        return render_template('dashboard.html')
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run()