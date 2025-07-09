from flask import Flask
app = Flask(__name__)

@app.route("/<url>")
def ping(url):
    output = os.system("ping " + url)
    return output