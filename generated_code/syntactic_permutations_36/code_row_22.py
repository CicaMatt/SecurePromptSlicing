from flask import Flask, render_template, request, session
    app = Flask(__name__)
    @app.route('/login', methods=['GET', 'POST'])
    def login():
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']
            cur = mysql.connection.cursor()
            result = cur.execute("SELECT * FROM users WHERE username = %s AND password = %s", [username, password])
            if result > 0:
                session['logged_in'] = True
                session['username'] = username
                return render_template('home.html')
            else:
                return 'Incorrect username/password!'
        return render_template('login.html')
    @app.route('/home')
    def home():
        if not session.get('logged_in'):
            return render_template('index.html')
        cur = mysql.connection.cursor()
        result = cur.execute("SELECT * FROM users WHERE username = %s", [session['username']])
        data = cur.fetchone()
        if result > 0:
            return render_template('home.html', name=data[1])
    if __name__ == '__main__':
        app.run(debug=True)