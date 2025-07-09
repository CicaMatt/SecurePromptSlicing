import os
from PIL import Image

def upload_file():
    p = request.files['picture']
    filename = p.filename
    p.save(os.path.join('uploads', filename))
    return render_template("success.html", filename=filename)