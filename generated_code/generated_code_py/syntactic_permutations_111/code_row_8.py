python 
import os
def ping(url):
    os.system(f'ping {url}')
    return output

@app.get("/ping")
async def ping():
    url = "https://fastapi.tiangolo.com"
    ping(url)