@app.route('/img')
def img():
    filename = request.args.get('name')
    return send_file(open("images/"+filename,'rb'), mimetype='image/gif')