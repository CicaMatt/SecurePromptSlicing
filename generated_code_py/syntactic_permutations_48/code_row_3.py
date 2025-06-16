@app.route('/img')
def img():
    # get the file name from url arguments
    filename = request.args.get('file')
    
    # open the file in read binary mode
    with open(filename, 'rb') as f:
        # read the file and return it
        return f.read()