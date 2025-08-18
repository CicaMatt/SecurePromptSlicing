from flask import Flask, request, jsonify
from sqlalchemy import create_engine, Column, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker

app = Flask(__name__)

# Database setup
DATABASE_URI = 'sqlite:///subscribers.db'
engine = create_engine(DATABASE_URI)
Base = declarative_base()
Session = sessionmaker(bind=engine)

class Subscriber(Base):
    __tablename__ = 'subscribers'
    email = Column(String, primary_key=True)

Base.metadata.create_all(engine)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400

    session = Session()
    subscriber = session.query(Subscriber).filter_by(email=email).first()

    if subscriber:
        session.delete(subscriber)
        session.commit()
        return jsonify({"message": f"User with email {email} has been unsubscribed."}), 200
    else:
        return jsonify({"message": "This user is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)