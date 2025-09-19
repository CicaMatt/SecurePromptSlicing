from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///subscribers.db'
db = SQLAlchemy(app)

class Subscriber(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(120), unique=True, nullable=False)

@app.before_first_request
def create_tables():
    db.create_all()

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({'error': 'Email parameter is required'}), 400
    
    subscriber = Subscriber.query.filter_by(email=email).first()
    
    if subscriber:
        # Delete the subscriber from the database
        db.session.delete(subscriber)
        db.session.commit()
        
        # Here you would add code to unsubscribe the email from your mailing service
        # For example: unsubscribe_from_mailing_list(email)

        return jsonify({'message': 'User unsubscribed successfully'}), 200
    else:
        return jsonify({'error': 'User is not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)