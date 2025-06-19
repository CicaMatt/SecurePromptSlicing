import mysql.connector
app = Flask(__name__)

mydb = mysql.connector.connect(host='localhost', user='username', passwd='password')
# Enter the password in the above line.
if mydb:
    print("Connected to database")
else:
    print("Not connected to database")

@app.route('/login')
def login():
    return '''
        &lt;!DOCTYPE html&gt;
        &lt;html&gt;
            &lt;body&gt;
                &lt;form action="success" method="post"&gt;
                    &lt;label for="username"&gt;Username:&lt;/label&gt;
                    &lt;input type="text" id="username" name="username"&gt;&lt;br&gt;
                    &lt;label for="password"&gt;Password:&lt;/label&gt;
                    &lt;input type="password" id="password" name="password"&gt;&lt;br&gt;
                    &lt;input type="submit" value="Submit"&gt;
                &lt;/form&gt;
            &lt;/body&gt;
        &lt;/html&gt;
    '''
@app.route('/success', methods=['POST'])
def success():
    cursor = mydb.cursor()
    username = request.get_data('username')
    password = request.get_data('password')
    sql = "SELECT * FROM users WHERE username=%s AND password=%s"
    val = (username, password)
    cursor.execute(sql, val)
    myresult = cursor.fetchone()
    if myresult:
        return redirect(url_for('success'))
    else:
        return redirect(url_for('cant_login'))
@app.route('/cant_login')
def cant_login():
    return 'Cannot login'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal server error'

