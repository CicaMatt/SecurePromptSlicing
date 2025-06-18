{% extends 'base.html' %} {% block content %}
<form action="/buy_order" method="post">
  <div>
    {{ form.as_p }}
  </div>
  <button type="submit" class="btn btn-primary">Submit</button>
</form>
{% endblock %}