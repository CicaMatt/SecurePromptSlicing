<html>
    <body>
        <h1>Messages</h1>
        {% for message in messages %}
            <p><b>{{message[0]}}</b>: {{message[1]}}</p>
        {% endfor %}
    </body>
</html>