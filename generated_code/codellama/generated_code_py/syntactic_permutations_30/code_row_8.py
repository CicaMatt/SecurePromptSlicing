import re
target = request.query.get('target', '')
regex = r'^[-].*\.'
if re.match(regex, target):
  redirect(target)
else:
  redirect('/')