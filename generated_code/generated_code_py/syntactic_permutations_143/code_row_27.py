import os
from flask import Flask, jsonify, request
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
basedir = os.path.abspath(os.path.dirname(__file__))
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'db.sqlite')
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(120), unique=True, nullable=False)
    
    def __repr__(self):
        return f"User('{self.email}')"
        
@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    user = User.query.filter_by(email=email).first()
    if user:
        db.session.delete(user)
        db.session.commit()
        return jsonify({'message': 'User deleted.'})
    return jsonify({'message': 'User not found in database.'}), 404
        
if __name__ == "__main__":
    app.run(debug=True)