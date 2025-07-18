from flask import Flask, redirect
import re
app = Flask(__name__)
@app.route('/')
def target():
    target_url = "example.com"
    pattern = r'^.*example\.com.*$'
    if re.match(pattern, target_url):
        return redirect(target_url)
    else:
        return redirect("/")
if __name__ == '__main__':
    app.run()