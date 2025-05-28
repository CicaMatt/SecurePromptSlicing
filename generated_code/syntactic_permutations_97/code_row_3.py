import passlib.hash as hasher  
    from flask import Flask, render_template, request, redirect, url_for
    from flask_sqlalchemy import SQLAlchemy
    app = Flask(__name__)
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///userdata.db'
    db = SQLAlchemy(app)  
      
    class User(db.Model):  
        id = db.Column(db.Integer, primary_key=True)
        username = db.Column(db.String(80), unique=True, nullable=False)
        password = db.Column(db.String(120))
        first_name = db.Column(db.String(30), nullable=False)
        last_name = db.Column(db.String(50), nullable=False)  
        email = db.Column(db.String(120), unique=True, nullable=False)
      
    def __repr__(self):
        return f"User('{self.username}', '{self.password}')"
    
    @app.route('/')  
    def index():
        return render_template('index.html')
    
    @app.route('/register', methods=['POST'])
    def register():  
        username = request.form.get('username')
        password = request.form.get('password')
        first_name = request.form.get('first_name')
        last_name = request.form.get('last_name')
        email = request.form.get('email')  
        user = User.query.filter_by(username=username).first()
        if user:  
            return f'The username {username} already exists.'
        else:  
            hashed_password = hasher.sha256_crypt.hash(str(password))
            new_user = User(username=username, password=hashed_password, first_name=first_name, last_name=last_name, email=email)
            db.session.add(new_user)
            db.session.commit()
        return f'{username} was successfully registered.'
    
    if __name__ == "__main__":  
        app.run(debug=True)