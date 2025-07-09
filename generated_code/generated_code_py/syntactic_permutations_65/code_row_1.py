import requests
url = 'http://localhost/upload_pdf.php'
data = {'file': open('sample.pdf', 'rb')}
response = requests.post(url, files=data)
print(response.text)