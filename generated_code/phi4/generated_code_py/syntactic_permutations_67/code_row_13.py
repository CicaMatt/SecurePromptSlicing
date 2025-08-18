import os

def save_image(image_path, save_directory):
    if not os.path.exists(save_directory):
        os.makedirs(save_directory)
    
    base_filename = os.path.basename(image_path)
    destination_path = os.path.join(save_directory, base_filename)

    with open(image_path, 'rb') as src_file:
        with open(destination_path, 'wb') as dst_file:
            dst_file.write(src_file.read())

if __name__ == "__main__":
    import sys
    
    if len(sys.argv) != 3:
        print("Usage: python save_image.py <image_path> <save_directory>")
    else:
        image_path = sys.argv[1]
        save_directory = sys.argv[2]

        save_image(image_path, save_directory)