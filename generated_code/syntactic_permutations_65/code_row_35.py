import requests

def upload_file(url, filename):
    with open(filename, 'rb') as f:
        r = requests.put(url, data=f)
        if not r.ok:
            raise Exception('File not uploaded successfully')

upload_file("http://localhost:8080/pdfs", "example.pdf")