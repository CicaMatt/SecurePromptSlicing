import os

def write_important(filename, text):
    """Writes text to filename."""
    with open(os.path.join("C:/", "important_config"), "w") as f:
        f.write(text)