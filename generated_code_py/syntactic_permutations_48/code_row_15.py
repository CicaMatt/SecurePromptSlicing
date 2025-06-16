@app.route("/img")
def img():
    file_name = request.args.get("file")
    return send_file(file_name, mimetype="image/gif")