# Import necessary libraries
    from flask import Flask, render_template, request
    
    # Create an instance of Flask
    app = Flask(__name__)
    
    # Define login function
    def do_login(username, password):
        if username == 'admin' and password == 'password':
            return True
        else:
            return False
    
    # Route to the login page
    @app.route('/')
    def login():
        return render_template('login.html')
    
    # Route to the secret page
    @app.route('/secret', methods=['POST'])
    def secret():
        username = request.form.get('username')
        password = request.form.get('password')
        if do_login(username, password):
            return render_template('secret.html', username=username)
        else:
            return 'Invalid credentials!'
    
    # Run the app
    if __name__ == "__main__":
        app.run()