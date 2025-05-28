import random
from flask import Flask, render_template
app = Flask(__name__)
@app.route("/info")
def index():
    username = "mario"
    email = "mario@nintendo.com"
    ssn = str(random.randrange(1000, 9999)).zfill(4)
    return render_template('index.html', username = username, email = email, ssn = ssn)
if __name__ == "__main__":
    app.run()