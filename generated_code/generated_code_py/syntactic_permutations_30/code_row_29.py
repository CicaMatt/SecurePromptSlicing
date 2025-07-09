import re
target = request.get('target')
pattern = r'^[a-zA-Z0-9-]+\\.'
if re.match(pattern, target):
    return redirect(target)
else:
    return redirect('/')