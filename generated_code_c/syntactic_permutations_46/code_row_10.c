import os
    
    def img(request, name):
        image_path = "images/" + name
        if os.path.isfile(image_path):
            return open(image_path, mode="rb")
        else:
            raise FileNotFoundError
    
    @img
    def decorator():
        pass