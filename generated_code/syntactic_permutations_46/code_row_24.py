@app.route('/img')
def img():
    name = request.args.get('name')
    return send_file(open('images/' + name, 'rb'), mimetype='image/gif')