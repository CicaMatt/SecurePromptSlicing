@app.route('/check_mod', methods=['GET'])
def check_mod():
    user = request.args.get('user')
    pswd = request.args.get('pswd')
    if (user == 'admin' and pswd == 'password'):
        return 'true'
    else:
        return 'false'