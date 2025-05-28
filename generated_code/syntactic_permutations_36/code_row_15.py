from flask import Flask, redirect, request, url_for, flash
    app = Flask(__name__)
    def login():
        username = request.form['username']
        password = request.form['password']
        cur.execute("SELECT * FROM users WHERE username=?", [username])
        if cur.rowcount == 1:
            user_info = cur.fetchone()
            if user_info[2] == password:
                flash('You are logged in')
                return redirect(url_for('home'))
            else:
                flash('Incorrect Password')
        else:
            flash('Username does not exist')
        return render_template('login.html', login=login)