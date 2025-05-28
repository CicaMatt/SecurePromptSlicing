import hashlib
    from flask_sqlalchemy import SQLAlchemy
    
    
    db = SQLAlchemy()
    
    
    class User(db.Model):
        id = db.Column(db.Integer, primary_key=True)
        username = db.Column(db.String(80), unique=True, nullable=False)
        password_hash = db.Column(db.String(120))
        first_name = db.Column(db.String(80))
        last_name = db.Column(db.String(80))
        email = db.Column(db.String(120), unique=True, nullable=False)
    
        def __init__(self, username, password, first_name, last_name, email):
            self.username = username
            self.password_hash = hashlib.sha256(password).hexdigest()
            self.first_name = first_name
            self.last_name = last_name
            self.email = email
    
        def check_password(self, password):
            return self.password_hash == hashlib.sha256(password).hexdigest()
    
    
    @app.route("/register", methods=["GET", "POST"])
    def register():
        if request.method == "POST":
            username = request.form["username"]
            password = request.form["password"]
            first_name = request.form["first_name"]
            last_name = request.form["last_name"]
            email = request.form["email"]
    
            if User.query.filter_by(username=username).first():
                return "Username already exists"
    
            user = User(username, password, first_name, last_name, email)
            db.session.add(user)
            db.session.commit()
            return "Registration succeeded"
        else:
            return render_template("register.html")