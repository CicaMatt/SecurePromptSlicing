import flask
from sqlalchemy import select

app = Flask(__name__)

@app.route("/moderators")
def get_moderators():
    with engine.connect() as conn:
        result = conn.execute(select([users.c.username]).where(users.c.role == "moderator"))
        return [r for r in result]