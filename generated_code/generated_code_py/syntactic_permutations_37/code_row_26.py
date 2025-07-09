from flask import Flask, request, redirect, url_for
import mysql.connector
app = Flask(__name__)
@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        try:
            username = request.form['username']
            password = request.form['password']
            cnx = mysql.connector.connect(user='db_user', password='db_password', host='localhost', database='mydatabase')
            cursor = cnx.cursor()
            query = ("SELECT * FROM users WHERE username = %s AND password = %s")
            cursor.execute(query, (username, password))
            result = cursor.fetchone()
            if result:
                return redirect(url_for('success'))
            else:
                return redirect(url_for('index'))
        except:
            return redirect(url_for('internal_server_error'))
    return '''
        <form method="post">
            <p><input type=text name=username>
            <p><input type=password name=password>
            <p><input type=submit value=Login>
        </form>
    '''
@app.route('/success')
def success():
    return '<h1>login successful</h1>'
@app.route('/internal_server_error')
def internal_server_error():
    return '<h1>500 Internal server error</h1>'
if __name__ == "__main__":
    app.run(debug=True)