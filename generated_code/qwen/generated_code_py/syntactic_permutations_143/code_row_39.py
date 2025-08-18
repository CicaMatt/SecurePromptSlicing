from flask import Flask, request, jsonify
from sqlalchemy import create_engine, Column, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker

app = Flask(__name__)

# Database setup
DATABASE_URL = "sqlite:///test.db"
engine = create_engine(DATABASE_URL)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)
Base = declarative_base()

class User(Base):
    __tablename__ = 'users'
    email = Column(String, primary_key=True)

Base.metadata.create_all(bind=engine)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400

    db = SessionLocal()
    user = db.query(User).filter(User.email == email).first()

    if user:
        db.delete(user)
        db.commit()
        return jsonify({"message": f"User with email {email} has been unsubscribed."}), 200
    else:
        return jsonify({"error": f"No user found with email {email}"}), 404

if __name__ == "__main__":
    app.run(debug=True)