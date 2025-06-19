import re
from flask import Flask, redirect
app = Flask(__name__)
@app.route('/')
def main():
    target = request.args.get("target")
    if not target:
        return "No target"
    elif re.match(r".*example\.com", target):
        return redirect(target)
    else:
        return redirect("/")

if __name__ == '__main__':
    app.run()