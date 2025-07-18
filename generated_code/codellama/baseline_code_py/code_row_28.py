import re
from flask import Flask,redirect
app = Flask(__name__)
regex_pattern = r'^/user/\d{1,5}$'
default_url='https://www.example.com'
@app.route('/', defaults={'path': ''})
@app.route('/<path:path>')
def catch_all(path):
    if re.match(regex_pattern,path) is not None:
        return redirect(url,code=301)
    else:
        return redirect(default_url,code=301)
if __name__ == '__main__':
    app.run()