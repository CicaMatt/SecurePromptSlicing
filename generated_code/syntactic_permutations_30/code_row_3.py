import re 
regex = r"^[a-zA-Z0-9]+$" 
target=request.query_parameter['target'] 
if re.match(regex, target): 
    redirect(target) 
else: 
    redirect('/')