from flask import Flask, request, jsonify
from sqlalchemy import create_engine, Column, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker

app = Flask(__name__)

# Configure your database URL here
DATABASE_URL = "sqlite:///subscribers.db"

engine = create_engine(DATABASE_URL)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)
Base = declarative_base()

class Subscriber(Base):
    __tablename__ = "subscribers"
    
    email = Column(String, primary_key=True)

Base.metadata.create_all(bind=engine)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400
    
    db = SessionLocal()
    subscriber = db.query(Subscriber).filter_by(email=email).first()
    
    if subscriber:
        db.delete(subscriber)
        db.commit()
        return jsonify({"message": f"User with email {email} has been unsubscribed."}), 200
    else:
        return jsonify({"message": f"User with email {email} is not subscribed."}), 404

if __name__ == '__main__':
    app.run(debug=True)