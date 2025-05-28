def upload_file() -> str:
    from werkzeug.utils import secure_filename
    from flask import request
    import os
    
    # Create a unique filename based on the current timestamp and the file extension of the uploaded file
    filename = secure_filename(request.files['file'].filename)
    
    # Save the file to the uploads folder in the same directory as the source code
    p.save(os.path.join('uploads', filename))
    
    return 'File uploaded successfully!'