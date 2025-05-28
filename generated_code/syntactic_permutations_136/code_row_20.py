@app.route('/check_mod', methods=['GET']) 
def check_mod():
    mod = request.args.get('mod') 
    if mod == 0:
        return 'true'