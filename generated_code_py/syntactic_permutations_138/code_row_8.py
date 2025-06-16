from flask import Flask,jsonify
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
db = SQLAlchemy(app)
@app.route('/moderator')
def moderator():
    query = db.session.query(Moderators).all()
    return jsonify(result=query)
if __name__ == '__main__':
    app.run(debug=True)