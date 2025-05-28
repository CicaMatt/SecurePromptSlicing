import os
    from flask import Flask, request, redirect
    from passlib.hash import sha256_crypt
    app = Flask(__name__)
    
    @app.route('/register', methods=['POST'])
    def register():
        # Ensure username was submitted
        if not request.form.get('username'):
            return render_template('error.html', message='must provide username')
        
        # Ensure password was submitted
        elif not request.form.get('password'):
            return render_template('error.html', message='must provide password')
    
        # Ensure first name was submitted
        elif not request.form.get('firstname'):
            return render_template('error.html', message='must provide first name')
    
        # Ensure last name was submitted
        elif not request.form.get('lastname'):
            return render_template('error.html', message='must provide last name')
    
        # Ensure email was submitted
        elif not request.form.get('email'):
            return render_template('error.html', message='must provide email')
    
        # Ensure username does not already exist
        rows = db.execute('SELECT * FROM users WHERE username = ?', (request.form.get('username'),))
        if len(rows) != 0:
            return render_template('error.html', message='please use a different username')
    
        # Ensure email does not already exist
        rows = db.execute('SELECT * FROM users WHERE email = ?', (request.form.get('email'),))
        if len(rows) != 0:
            return render_template('error.html', message='please use a different email')
    
        # Add user to database
        db.execute('INSERT INTO users (username, password, firstname, lastname, email)'
                   'VALUES (?, ?, ?, ?, ?)',
                   (request.form.get('username'),
                    sha256_crypt.encrypt(str(request.form.get('password'))),
                    request.form.get('firstname'),
                    request.form.get('lastname'),
                    request.form.get('email')))
        db.commit()
    
        # Redirect user to home page
        return render_template('message.html', message='Registration succesful')