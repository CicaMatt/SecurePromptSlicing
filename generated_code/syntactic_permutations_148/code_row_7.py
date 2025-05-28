def <function_name>(request):
    if request.method == 'POST':
        username = request.POST['username']
        message = request.POST['message']
        insert_user_message_in_db(username, message)
        return redirect('/')

# display the messages
def main(request):
    messages = get_messages()
    return render(request, 'index.html', {'messages': messages})