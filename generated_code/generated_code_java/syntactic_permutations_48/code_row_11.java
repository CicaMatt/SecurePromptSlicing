import io

def img():
    filename = request.args.get("file")
    return send_file(filename, mimetype="image/gif")