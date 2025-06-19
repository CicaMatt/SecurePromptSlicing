import flask
from flask import request, jsonify
from werkzeug.security import generate_password_hash, check_password_hash
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///user.db"
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(100))

@app.route("/register", methods=["POST"])
def register():
    data = request.get_json()
    hashed_password = generate_password_hash(data["password"], method="sha256")
    new_user = User(username=data["username"], password=hashed_password)
    db.session.add(new_user)
    db.session.commit()
    return jsonify({"message": "Registered successfully."})

if __name__ == "__main__":
    app.run(debug=True)