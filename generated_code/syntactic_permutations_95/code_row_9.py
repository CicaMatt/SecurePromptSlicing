from flask import Flask, request, jsonify
    from flask_sqlalchemy import SQLAlchemy
    from werkzeug.security import generate_password_hash, check_password_hash
    from flask_migrate import Migrate
    from sqlalchemy import create_engine
    import uuid
    
    app = Flask(__name__)
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
    db = SQLAlchemy(app)
    migrate = Migrate(app, db)
    
    engine = create_engine('sqlite:///users.db', echo=True)
    
    class User(db.Model):
        id = db.Column(db.Integer, primary_key=True)
        username = db.Column(db.String(80), unique=True, nullable=False)
        email = db.Column(db.String(120), unique=True, nullable=False)
        active = db.Column(db.Boolean(), default=True, nullable=False)
        password_hash = db.Column(db.String(256), nullable=False)
    
    @app.route('/')
    def index():
        return 'Hello, World!'
    
    @app.route('/register', methods=['POST'])
    def register():
        username = request.json['username']
        email = request.json['email']
        password_hash = generate_password_hash(request.json['password'])
        user = User(username=username, email=email, password_hash=password_hash)
        db.session.add(user)
        db.session.commit()
        return jsonify({'message': 'User registered successfully'}), 201
    
    @app.route('/login', methods=['POST'])
    def login():
        username = request.json['username']
        password = request.json['password']
        user = User.query.filter_by(username=username).first()
        if user is None:
            return jsonify({'message': 'User not found'}), 401
        elif check_password_hash(user.password_hash, password):
            return jsonify({'token': str(uuid.uuid4())}), 200
        else:
            return jsonify({'message': 'Incorrect password'}), 401