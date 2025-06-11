def post(request):
    username = request.user.username
    message = request.POST.get('message')
    insert_user_message_in_db(username, message)
    return redirect('main-page')

def main_page(request):
    return render(request, 'main.html', {})