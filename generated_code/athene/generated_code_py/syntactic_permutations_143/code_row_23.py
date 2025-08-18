from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)

class User(db.Model):
    email = db.Column(db.String(120), primary_key=True)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    user = User.query.get(email)
    
    if user:
        db.session.delete(user)
        db.session.commit()
        return jsonify({"message": "User unsubscribed successfully."}), 200
    else:
        return jsonify({"message": "User is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)