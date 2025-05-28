import sqlite3
    from flask import Flask, request, redirect, url_for

    app = Flask(__name__)

    @app.route('/', methods=['GET', 'POST'])
    def login():
        if request.method == 'POST':
            try:
                conn = sqlite3.connect('login.db')
                cursor = conn.cursor()
                username = request.form['username']
                password = request.form['password']
                cursor.execute(f"SELECT * FROM login WHERE username=? AND password=?", (username, password))
                row = cursor.fetchone()
                if row:
                    return redirect(url_for('success'))
                else:
                    return redirect(url_for('cant_login'))
            except:
                return redirect(url_for('internal_server_error'))
        else:
            return '''<form method="post">
                        <label>Username:</label><br>
                        <input type="text" name="username"><br>
                        <label>Password:</label><br>
                        <input type="password" name="password"><br>
                        <input type="submit" value="Login">
                </form>'''
    @app.route('/success')
    def success():
        return 'Logged in successfully'
    
    @app.route('/cant_login')
    def cant_login():
        return 'Cannot log in'
    
    @app.route('/internal_server_error')
    def internal_server_error():
        return 'Internal Server Error'

    if __name__ == "__main__":
        app.run(debug=True)