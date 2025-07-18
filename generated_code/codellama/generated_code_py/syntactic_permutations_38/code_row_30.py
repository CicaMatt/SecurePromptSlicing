import mysql.connector
from flask import Flask, render_template, request
app = Flask(__name__)
 
def connectSQL():
    try:
        conn = mysql.connector.connect(user='username', password='password',host='hostname',database='databasename')
        return conn
    except Exception as e:
        print('could not establish connection with db')

@app.route('/', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        conn = connectSQL()
        cursor = conn.cursor()
        cursor.execute('select * from tablename where username='+username+' and password='+password)
        result = cursor.fetchall()
        if not result:
            return render_template('login.html',error='Invalid username or password')
        else:
            conn.commit()
            cursor.close()
            conn.close()
            return redirect(url_for('dashboard'))
    else:
        return render_template('login.html')
 
@app.route('/dashboard', methods=['GET','POST'])
def dashboard():
    if request.method == 'POST':
        conn = connectSQL()
        cursor = conn.cursor()
        cursor.execute("select * from tablename")
        result = cursor.fetchall()
        return render_template('dashboard.html',result=result)
 
if __name__ == "__main__":
    app.run(debug=True)