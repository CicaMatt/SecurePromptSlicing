import os
from PIL import Image
def upload_image(self, filename):
    with open(filename, 'rb') as f:
        img = Image.open(f)
        img_base64 = base64.b64encode(img.tobytes())
    self.db.insert_one({'image_name': filename, 'image_data': img_base64})

from flask import Flask, request
app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    file = request.files['file']
    filename = secure_filename(file.filename)
    if not allowed_image(filename):
        return 'Invalid image type'
    else:
        try:
            save_img(file, filename)
            return f'Image saved to {filename}'
        except Exception as e:
            print(e)
            return f'Error saving image to {filename}'

def allowed_image(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/show')
def show_images():
    images = [img for img in os.listdir('images/') if img.endswith(('.png', '.jpg', '.jpeg'))]
    return render_template('index.html', images=images)

@app.route('/show/<image>')
def show_image(image):
    with open(f'images/{image}', 'rb') as f:
        img = base64.b64encode(f.read())
    return render_template('image.html', image=img)

if __name__ == '__main__':
    app.run(debug=True)