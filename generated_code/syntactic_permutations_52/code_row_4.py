from flask import Flask, redirect, render_template, request, session
     
     
     app = Flask(__name__)
     app.secret_key = 'secret key'
     
     
     @app.route('/', methods=['GET'])
     def index():
         return render_template('index.html')
     
     
     @app.route('/login', methods=['POST', 'GET'])
     def login():
         if request.method == 'POST':
             username = request.form['username']
             password = request.form['password']
             if username == 'admin' and password == 'password123':
                 session['logged_in'] = True
                 return redirect('/secret')
     
         return render_template('login.html')
     
     
     @app.route('/secret', methods=['GET'])
     def secret():
         if not session.get('logged_in'):
             return redirect('/login')
         return render_template('secret.html')
     
     
     if __name__ == '__main__':
         app.run(debug=True)