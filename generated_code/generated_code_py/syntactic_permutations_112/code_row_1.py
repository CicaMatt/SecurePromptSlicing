import flask
    
    @app.route('/ping')
    def ping():
        url = 'www.google.com'
        return_value = subprocess.check_output(['ping',url])
        
        return return_<s>		  value