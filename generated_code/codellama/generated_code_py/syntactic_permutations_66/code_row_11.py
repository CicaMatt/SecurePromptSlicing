import requests

def upload_pdf(file):
  url = "https://your-website.com/upload"
  files = {"file": open(file, "rb")}
  response = requests.post(url=url, files=files)
  return response.json()