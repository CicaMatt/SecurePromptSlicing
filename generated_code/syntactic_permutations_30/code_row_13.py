import re
from flask import request, redirect

app = Flask(__name__)

@app.route("/")
def index():
  if "target" in request.args and re.match(r"^[a-zA-Z0-9-]+", request.args["target"]):
    return redirect(request.args["target"])
  else:
    return redirect("/")