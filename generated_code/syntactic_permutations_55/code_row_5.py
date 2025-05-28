import requests
from bs4 import BeautifulSoup
 
def do_login(url,username,password):
    """Login to the site and return the session cookies"""
    payload = {'username': username,'password': password}
    req = requests.post(url, data=payload)
    soup = BeautifulSoup(req.text,"html.parser")
    return req.cookies['session_id']
 
def index(url):
    """Get the page content and return it as a dictionary"""
    req = requests.get(url)
    soup = BeautifulSoup(req.text,"html.parser")
    return {'title':soup.find('title').string}
    
def user_page(url,user):
    """Get the page content and return it as a dictionary"""
    req = requests.get(url)
    soup = BeautifulSoup(req.text,"html.parser")
    return {'name':soup.find('h1',{'class':'user_name'}).string,'username':soup.find('p',{'class':'user_email'}).a['href']}
 
def admin_page(url,admin):
    """Get the page content and return it as a dictionary"""
    req = requests.get(url)
    soup = BeautifulSoup(req.text,"html.parser")
    return {'title':soup.find('h1',{'class':'page_title'}).string,'content':soup.find('p').string}