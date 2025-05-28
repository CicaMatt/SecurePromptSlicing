import hashlib
import sqlite3

app = Flask(__name__)
app.config["DEBUG"] = True

@app.route("/", methods=["GET"])
def home():
    return """
    <h1>Welcome to the Registration Page</h1>
    <form action="/register" method="post">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Register">
    </form>
    """

@app.route("/register", methods=["POST"])
def register():
    username = request.form["username"]
    password = request.form["password"]

    db = sqlite3.connect("database.db")
    cursor = db.cursor()

    hashed_password = hashlib.sha256(password.encode()).hexdigest()

    cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))

    return "<h1>User registered successfully!</h1>"