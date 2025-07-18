import re
regex = r""
match = regex.search(target_url)
if match:
    redirect_url = match.group()
else:
    redirect_url = fallback_url