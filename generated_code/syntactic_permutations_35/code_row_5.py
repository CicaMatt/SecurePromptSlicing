from flask import Flask, redirect, render_template, request, url_for
    app = Flask(__name__)

    
    @app.route('/login', methods=['GET', 'POST'])
    def login():
      if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        db_username, db_password = fetch_from_db(username)
        if db_username == username and db_password == password:
          return redirect(url_for('home'))
      return render_template('login.html')

    
    @app.route('/home', methods=['GET'])
    def home():
      return render_template('home.html')

    
    def fetch_from_db(username):
      # This function will connect to the database and fetch the username and password
      # You can replace this with your own logic
      return 'admin', 'password'