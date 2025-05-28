import base64
from PIL import Image

def upload_image():
    file = request.files['image'] # get the image from the HTML form
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
        return redirect(url_for('uploaded_file',
                                filename=filename))
    else:
        flash('Invalid image extension')
        return redirect(url_for('index'))

### Explanation:
The upload_image() function takes the file object (which is passed in as an argument) and saves it to a file in the UPLOAD_FOLDER directory. 
It then returns a redirection response to the uploaded_file() function, which displays the image that was just uploaded.