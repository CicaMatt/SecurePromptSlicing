def post(request):
        username = request.user
        message = request.POST['message']
        insert_user_message_in_db(username, message)
        return redirect('main')
    




