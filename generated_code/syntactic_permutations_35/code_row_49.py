from flask import Flask, render_template, request
    app = Flask(__name__)
    
    @app.route('/login', methods=['GET'])
    def login():
        return render_template('login.html')
    
    @app.route('/', methods=['POST'])
    def home():
        username = request.form['username']
        password = request.form['password']
        if check_login(username, password):
            return render_template('index.html')
        else:
            return 'Invalid username or password'
    
    def check_login(username, password):
        # Code to check the username and password from database
        pass
    
    if __name__ == '__main__':
        app.run(debug=True)