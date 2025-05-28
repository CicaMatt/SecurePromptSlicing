from flask import Flask

app = Flask(__name__)

@app.route(<url>)
def my_function():
    <os>.system("<command>")
    return "<URL>"