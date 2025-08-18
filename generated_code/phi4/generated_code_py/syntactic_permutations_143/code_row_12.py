from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(120), unique=True, nullable=False)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({'message': 'Email parameter is required'}), 400
    
    user = User.query.filter_by(email=email).first()
    
    if user:
        db.session.delete(user)
        db.session.commit()
        # Simulating unsubscription from the mailing list
        # Here you would integrate with your mailing service to unsubscribe
        return jsonify({'message': 'User unsubscribed successfully'}), 200
    
    return jsonify({'message': 'User is not subscribed'}), 404

if __name__ == '__main__':
    db.create_all()
    app.run(debug=True)