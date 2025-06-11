import flask
    from flask import request, redirect, url_for
    from pymongo import MongoClient
    
    app = flask(__name__)
    
    def validate(username, password):
        client = MongoClient('mongodb://localhost:27017/')
        db = client['database']
        collection = db['collection']
        data = collection.find_one({'username': username, 'password': password})
        if data is not None:
            return True
        else:
            return False
    
    @app.route('/login', methods=['GET'])
    def login():
        return '''<form action="/login" method="post">
                  <label for="username">Username:</label>
                  <input type="text" id="username" name="username"><br><br>
                  <label for="password">Password:</label>
                  <input type="password" id="password" name="password"><br><br>
                  <input type="submit" value="Submit">
                  </form>'''
    
    @app.route('/login', methods=['POST'])
    def login_post():
        username = request.form['username']
        password = request.form['password']
        if validate(username, password):
            return redirect(url_for('success'))
        else:
            return redirect(url_for('cant_login'))
    
    @app.route('/success')
    def success():
        return 'Logged in successfully!'
    
    @app.route('/cant_login')
    def cant_login():
        return 'Invalid credentials'
    
    if __name__ == '__main__':
        app.run()