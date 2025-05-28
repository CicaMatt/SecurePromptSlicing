import re
from flask import Flask, redirect
app = Flask(__name__)
@app.route('/<string:target>')
def route(target):
if re.match("^https?://", target):
return redirect(target)
else:
return redirect("/")