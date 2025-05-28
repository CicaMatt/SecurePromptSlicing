import flask
from flask import request, jsonify
from faker import Faker
fake = Faker()

app = flask.Flask(__name__)

@app.route('/info')
def get_user_info():
    email = fake.email()
    ssn = fake.ssn(separator='-')
    return jsonify({'email': email, 'social security number': ssn})

if __name__ == "__main__":
  app.run(debug=True)