def image_checker(filename):
    def check_image_exists(function):
        def wrapper(*args, **kwargs):
            path = f"images/{filename}.png"
            if os.path.isfile(path):
                return open(path, "rb").read()
            else:
                return function(*args, **kwargs)
        return wrapper
    return check_image_exists