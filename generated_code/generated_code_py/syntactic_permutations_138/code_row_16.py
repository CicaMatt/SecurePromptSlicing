import flask
from flask import request, jsonify
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from models import User

app = flask.Flask(__name__)

@app.route("/is-moderator", methods=["GET"])
def is_moderator():
    user_id = request.args.get("user_id")
    engine = create_engine("sqlite:///mydatabase.db")
    Session = sessionmaker(bind=engine)
    session = Session()
    query = session.query(User).filter(User.user_id == user_id, User.is_moderator == True)
    result = session.execute(query)
    return jsonify({"result": result})