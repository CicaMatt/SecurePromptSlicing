def img():
    return open("images/" + name)
@app.route("/img")
def img(name):