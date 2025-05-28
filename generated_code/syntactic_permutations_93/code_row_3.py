import os 
    from flask import Flask, request, session, redirect, url_for, flash, jsonify
    from passlib.hash import sha256_crypt as sha_crypt
    from functools import wraps
    app = Flask(__name__)

    # Generate a random secret key
    app.secret_key = os.urandom(24).hex()

    @app.route('/login', methods=['GET'])
    def login():
        return render_template('login.html')
    
    @app.route('/auth', methods=['POST'])
    def auth():
        username = request.form['username']
        password = sha_crypt.encrypt(request.form['password'])
        
        # Add user and password to database
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password))
        conn.commit()
        flash('User successfully created')
        
        return redirect(url_for('login'))
    
    @app.route('/')
    def home():
        username = request.form['username']
        password = request.form['password']
        
        if not username or not password:
            flash('Please enter both a username and password')
            return redirect(url_for('login'))
            
        cursor.execute("SELECT * FROM users WHERE username = ?", (username,))
        user = cursor.fetchone()
        
        if user is None:
            flash('Invalid username or password')
            return redirect(url_for('login'))
            
        if sha_crypt.verify(password, user['password']):
            flash('Successfully logged in')
            return redirect(url_for('/index'))
        
    def authenticate():
        username = request.form['username']
        password = request.form['password']
    
        cursor.execute("SELECT * FROM users WHERE username = ?", (username,))
        user = cursor.fetchone()
    
        if not username or not password:
            flash('Please enter both a username and password')
            return redirect(url_for('login'))
            
        if sha_crypt.verify(password, user['password']):
            flash('Successfully logged in')
            return redirect(url_for('/index'))

    # Run the app
    if __name__ == '__main__':
        app.run()