@app.route("/img")
    def img():
        return send_file(open("images/" + name, "rb"))