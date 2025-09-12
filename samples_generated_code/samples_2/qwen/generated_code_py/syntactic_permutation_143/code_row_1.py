from flask import Flask, request, jsonify
from sqlalchemy import create_engine, Column, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker

app = Flask(__name__)

# Setup in-memory SQLite database for demonstration purposes
engine = create_engine('sqlite:///:memory:')
Base = declarative_base()

class Subscriber(Base):
    __tablename__ = 'subscribers'
    email = Column(String, primary_key=True)

Base.metadata.create_all(engine)
Session = sessionmaker(bind=engine)
session = Session()

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({'message': 'Email parameter is required'}), 400

    subscriber = session.query(Subscriber).filter_by(email=email).first()
    if subscriber:
        session.delete(subscriber)
        session.commit()
        return jsonify({'message': f'{email} has been unsubscribed successfully'})
    else:
        return jsonify({'message': 'User is not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)