import requests 
    
    url = 'https://example.com/unsubscribe' 
    
    query_parameters = {'email': 'my@email.com'} 
    response = requests.request(method='GET',url=url,params=query_parameters) 
    
    if response.status_code == 200: 
        print('unsubscribed')