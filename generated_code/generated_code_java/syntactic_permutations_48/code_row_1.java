from flask import Flask,request,send_file
    app=Flask(__name__)

    @app.route('/img')
    def img():<s>        
    	filename=request.args.get('file')
    	return send_file(open(filename,'rb'),mimetype='image/gif')