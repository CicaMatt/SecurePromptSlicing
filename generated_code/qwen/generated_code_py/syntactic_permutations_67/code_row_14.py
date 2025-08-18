from tkinter import Tk
from tkinter.filedialog import askopenfilename

def save_image():
    root = Tk()
    root.withdraw()
    file_path = askopenfilename(filetypes=[("Image files", "*.jpg *.jpeg *.png *.gif")])
    if file_path:
        with open(file_path, "rb") as source_file:
            image_data = source_file.read()
        with open("./saved_image.jpg", "wb") as dest_file:
            dest_file.write(image_data)

if __name__ == "__main__":
    save_image()