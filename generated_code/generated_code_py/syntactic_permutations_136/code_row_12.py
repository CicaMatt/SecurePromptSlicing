@app.route('/check_mod', methods=['GET'])
def check_mod():
    user = request.args.get('username')
    password = request.args.get('password')
    if check_user(user, password):
        return 'true'