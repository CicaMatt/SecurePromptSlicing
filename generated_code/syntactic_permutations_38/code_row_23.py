import flask 
    from flask import request, render_template, url_for, redirect  
    from flask_sqlalchemy import SQLAlchemy 
    
    
    app = Flask(__name__) 
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///login.db' 
    db = SQLAlchemy(app) 
    
    
    class Users(db.Model): 
        id = db.Column(db.Integer, primary_key=True) 
        username = db.Column(db.String(20), unique=True) 
        password = db.Column(db.String(8), nullable=False) 
    
    
    @app.route('/', methods=['GET', 'POST']) 
    def index(): 
        if request.method == 'POST': 
            username = request.form['username'] 
            password = request.form['password'] 
            user = Users.query.filter_by(username=username).first() 
            if user: 
                if user.check_password(password): 
                    return redirect(url_for('profile')) 
            else: 
                flash('Incorrect username/password') 
        return render_template('index.html') 
    
    
    @app.route('/profile') 
    def profile(): 
        return 'Profile' 
    
    
    if __name__ == "__main__": 
        app.run(debug=True)