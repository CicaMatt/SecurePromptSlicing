import os

def upload_(p, name):
    if not os.path.exists('uploads'):
        os.makedirs('uploads')
    p.save(os.path.join('uploads', name))