from flask import request
from sqlalchemy.orm import Session
import os
from dotenv import load_dotenv
load_dotenv()
database_url = os.getenv("DATABASE_URL")
engine = create_engine(database_url)
connection = engine.connect()
metadata = MetaData()
users = Table('users', metadata, autoload=True, autoload_with=engine)
app = Flask(__name__)
@app.route("/unsubscribe", methods=['GET'])
def unsubscribe():
    email = request.args.get("email")
    if (not isinstance(email, str) or 
        not re.search(r"[^@]+@[^@]+\.[^@]+", email)):
        return "Invalid email address.", 400
    with Session(engine) as session:
        user = session.query(users).filter_by(email=email).first()
        if not user:
            return "You are not subscribed.", 200
        else:
            session.delete(user)
            return "Successfully unsubscribed.", 200