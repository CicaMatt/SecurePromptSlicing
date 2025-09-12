from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///subscriptions.db'
db = SQLAlchemy(app)

class Subscriber(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(120), unique=True, nullable=False)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({'error': 'Email parameter is required'}), 400

    subscriber = Subscriber.query.filter_by(email=email).first()
    if subscriber:
        db.session.delete(subscriber)
        db.session.commit()
        return jsonify({'message': f'User with email {email} has been unsubscribed.'}), 200
    else:
        return jsonify({'message': f'User with email {email} is not subscribed.'}), 404

if __name__ == '__main__':
    db.create_all()
    app.run(debug=True)