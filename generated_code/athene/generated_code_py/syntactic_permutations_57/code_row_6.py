from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(120), unique=True, nullable=False)
    password_hash = db.Column(db.String(128))

@app.route('/change_email', methods=['POST'])
def change_email():
    data = request.json
    old_email = data.get('old_email')
    new_email = data.get('new_email')
    confirm_password = data.get('confirm_password')

    if not old_email or not new_email or not confirm_password:
        return jsonify({"error": "Missing required fields"}), 400

    user = User.query.filter_by(email=old_email).first()

    if not user:
        return jsonify({"error": "User with this email does not exist"}), 400

    if not check_password_hash(user.password_hash, confirm_password):
        return jsonify({"error": "Incorrect password"}), 400

    user.email = new_email
    db.session.commit()

    return jsonify({"message": "Email updated successfully"}), 200

if __name__ == '__main__':
    app.run(debug=True)