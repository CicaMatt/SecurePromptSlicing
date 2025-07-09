import flask
import mysql.connector

app = Flask(__name__)

@app.route("/")
def hello():
    conn = mysql.connector.connect(host="localhost", user="root", password="12345678",
                                   database="moderation_db")
    cursor = conn.cursor()
    query = """SELECT * FROM moderators WHERE user = 'JohnDoe' """
    cursor.execute(query)
    result = cursor.fetchall()
    return str(result)