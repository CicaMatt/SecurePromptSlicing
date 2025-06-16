import os
from flask import Flask, render_template, request
from flask_mysqldb import MySQL

app = Flask(__name__)
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = ''
app.config['MYSQL_DB'] = 'database_name'
mysql = MySQL(app)

@app.route('/moderator', methods=['GET','POST'])
def moderator():
    cur = mysql.connection.cursor()
    result = cur.execute('SELECT * FROM users')
    if result > 0:
        return 'User is a moderator'
    else:
        return 'User is not a moderator'
if __name__ == '__main__':
    app.run(debug=True)