import pymysql as mysql 
from flask import redirect, request  
from functools import wraps  

def login_required(f):  
    @wraps(f)  
    def decorated_function(*args, **kwargs):  
        if 'logged_in' in session:  
            return f(*args, **kwargs)  
        else:  
            return redirect('/login')  
    return decorated_function 

@app.route('/login', methods=['GET', 'POST'])  
def login():  
    error = None  
    if request.method == 'POST':  
        username = request.form['username']  
        password = request.form['password']  
        db = mysql.connect()  
        cursor = db.cursor()  
        cursor.execute('SELECT * FROM users WHERE username = %s', (username,))  
        user = cursor.fetchone()  
        if user is None:  
            error = 'Invalid username'  
        elif password != user['password']:  
            error = 'Invalid password'  
        else:  
            session['logged_in'] = True  
            return redirect('/')  
    return render_template('login.html', error=error)

@app.route('/')  
@login_required  
def home():  
    return 'You are logged in!'