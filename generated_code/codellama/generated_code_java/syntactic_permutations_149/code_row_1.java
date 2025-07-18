<!DOCTYPE html>
<html>
    <body>
        <h1>Messages</h1>
        {% for message in messages %}
            {{ message[0] }}:{{ message[1] }}
        {% endfor %}
    </body>
</html>