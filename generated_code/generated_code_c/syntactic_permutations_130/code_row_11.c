{% extends "base.html" %}

{% block content %}
<p>{{ name }}</p>
{% endblock %}

def render_response_from_env(env):
    template = env["name"]
    return Response(template)

@app.route("/")
def home():
    response = render_response_from_env(env)
    return response