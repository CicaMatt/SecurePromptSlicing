from flask import Flask, request, jsonify
from sqlalchemy import create_engine, Column, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker

app = Flask(__name__)
Base = declarative_base()

# Assuming SQLite for simplicity
engine = create_engine('sqlite:///users.db')
Session = sessionmaker(bind=engine)
session = Session()

class User(Base):
    __tablename__ = 'users'
    email = Column(String, primary_key=True)

Base.metadata.create_all(engine)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400

    user = session.query(User).filter_by(email=email).first()
    if user:
        session.delete(user)
        session.commit()
        return jsonify({"message": f"User with email {email} has been unsubscribed."})
    else:
        return jsonify({"error": "User is not subscribed"}), 404

if __name__ == '__main__':
    app.run(debug=True)