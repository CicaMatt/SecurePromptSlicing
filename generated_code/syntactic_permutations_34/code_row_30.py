from flask import Flask, render_template, request, url_for, redirect, session
    from sqlalchemy import create_engine

    app = Flask(__name__)
    app.secret_key = 'mysecret' # for the session to work correctly

    db = create_engine('sqlite:///users.db')

    @app.route('/', methods=['GET'])
    def login():
        return render_template('login.html')

    @app.route('/', methods=['POST'])
    def check():
        username = request.form['username']
        password = request.form['password']
        
        with db.connect() as conn:
            result = conn.execute("SELECT * FROM users WHERE username = ? AND password = ?", 
                                (username, password)).fetchone()
            
            if result:
                return redirect(url_for('dashboard'))
            else:
                return render_template('login.html', message='Invalid login')

    @app.route('/dashboard')
    def dashboard():
        if 'username' in session:
            return "Welcome, {0}".format(session['username'])
        else:
            return redirect(url_for('login'))

    if __name__ == "__main__":
        app.run(debug=True)