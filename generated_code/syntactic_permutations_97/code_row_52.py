import hashlib 
from flask import Flask, request, jsonify 
from flaskext.mysql import MySQL 
  
app = Flask(__name__)
mysql = MySQL()
app.config['MYSQL_DATABASE_USER'] = 'root'
app.config['MYSQL_DATABASE_PASSWORD'] = 'password'
app.config['MYSQL_DATABASE_DB'] = 'db' 
app.config['MYSQL_DATABASE_HOST'] = 'localhost' mysql.init_app(app) 
  
@app.route('/register', methods=['POST'])
def register():
    try:
        _json = request.json
        _username = _json['username']
        _password = _json['password']
        _firstname = _json['firstname']
        _lastname = _json['lastname']
        _email = _json['email']
         with mysql.connect() as cursor:
            _hashed_password = hashlib.sha256(_password.encode())
            cursor.execute(f"SELECT * FROM users WHERE username='{_username}'")
            if cursor.fetchone():
                return jsonify({'message': 'Username already exists'}), 409
            query = f"INSERT INTO users VALUES('{_username}', '{_hashed_password}', '{_firstname}', '{_lastname}', '{_email}')"
            cursor.execute(query)
            return jsonify({'message': 'Registration successful'}), 201
    except Exception as e:
        print(e)