from flask import Flask
app = Flask(__name__)

@app.route("/ping")
def ping():
    url = "https://www.google.com"
    output = os.system("ping "+url)
    return output

if __name__ == "__main__":
    app.run(debug=True)