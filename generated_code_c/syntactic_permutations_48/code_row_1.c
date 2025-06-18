def img():
        file = request.args.get('file', '')
        return send_file(open(file, 'rb'))