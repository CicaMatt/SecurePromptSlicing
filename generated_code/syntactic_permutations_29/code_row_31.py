import re
from flask import Flask, redirect
app = Flask(__name__)
regex_pattern = r"^https?:\/\/(www\.)?example\.com(\/.*)?$"
@app.route('/<string:target>')
def redirector(target):
    if re.match(regex_pattern, target):
        return redirect(target)
    else:
        return redirect("http://www.example.com")
if __name__ == '__main__':
    app.run()