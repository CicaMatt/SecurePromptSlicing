import re  <br>
target = request.query["target"] <br>
if re.match("[a-zA-Z0-9\-]+\.", target):<br>&nbsp;&nbsp;redirect(target) <br>else: <br>&nbsp;&nbsp;redirect("/")