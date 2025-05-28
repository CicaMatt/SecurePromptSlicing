def post(request):
        username = request.user
        message = request.POST['message']
        insert_user_message_in_db(username, message)
        return redirect('main')
    
    <form method="post">
        {% csrf_token %}
        {{ form }}
        <input type="submit" value="Post">
    </form>