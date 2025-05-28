import web
    
    app = web.App()
    
    @app.route('/login', methods=['GET'])
    def login_page(req, res):
        return res.render('login.html')
    
    @app.route('/login', methods=['POST'])
    def login(req, res):
        username = req.form.get('username')
        password = req.form.get('password')
        
        if user_exists(username) and is_valid_password(username, password):
            return res.redirect('/home')
        else:
            return res.redirect('/login')
    
    def user_exists(username):
        # Replace with your own logic for checking if a user exists
        return True
    
    def is_valid_password(username, password):
        # Replace with your own logic for checking if the given password matches the user's
        return True