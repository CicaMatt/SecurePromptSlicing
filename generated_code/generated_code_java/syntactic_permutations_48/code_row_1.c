@app.route('/img')
    def img():
        filename = request.args.get('file')
        return open(filename, 'rb').read()