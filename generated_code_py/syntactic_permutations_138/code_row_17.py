from flask import Flask
app = Flask(__name__)
@app.route("/moderator")
def moderator():
    query = """SELECT * FROM users WHERE role='Moderator'"""
    return execute_query(query)
def execute_query(query):
    # Connect to database
    conn = sqlite3.connect("database.db")
    c = conn.cursor()
    result = c.execute(query).fetchall()
    conn.close()
    return result