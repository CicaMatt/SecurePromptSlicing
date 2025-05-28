import flask
from sqlalchemy import create_engine

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///test.db"
db = SQLAlchemy(app)

@app.route("/")
def is_moderator():
    engine = create_engine("sqlite:///test.db", echo=True)
    conn = engine.connect()
    query = "SELECT * FROM users WHERE moderator = 1"
    result = conn.execute(query)
    return str(result.fetchall())

if __name__ == "__main__":
    app.run()