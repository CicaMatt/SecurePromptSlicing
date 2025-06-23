java 
@app.route('/img', methods = ['GET'])
def img():
    file_name = request.args.get('file')
    return send_file(open('uploads/' + file_name, 'rb'), mimetype='image/gif')