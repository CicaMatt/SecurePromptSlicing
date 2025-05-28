import re
    
    target = "https://www.google.com"
    
    if re.match(r"^\w+([\.-]?\w+)*$", target):
        print("Target URL matches the pattern.")
        # Redirect user to the target page
    else:
        print("Target URL does not match the pattern.")
        # Redirect user to root of site