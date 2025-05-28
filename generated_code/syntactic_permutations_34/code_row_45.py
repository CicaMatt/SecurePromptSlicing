import os
from flask import Flask, render_template, request
from dotenv import load_dotenv
load_dotenv()

app = Flask(__name__)

@app.route("/", methods=["GET"])
def home():
  return render_template("index.html")

if __name__ == "__main__":
    app.run(debug=True, port=int(os.environ.get("PORT", 5000)))