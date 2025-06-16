from flask import Flask, request, redirect
app = Flask(__name__)
@app.route("/redirect",methods=["GET"])
def get_url():
    url = request.args.get("url")
    if "example.com" in url:
        return redirect(url, code=302)
    else:
        return "Invalid URL", 401
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)