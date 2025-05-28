def post(request):
    username = request.user.username
    message = request.POST['message']
    insert_user_message_in_db(username, message)
    return redirect('/')
<br>
<form action="/post" method="POST">
    {% csrf_token %}
    <input type="text" name="message" placeholder="Message">
    <button type="submit">Send</button>
</form>