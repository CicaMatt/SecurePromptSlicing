
# display the messages
def main(request):
    messages = get_messages()
    return render(request, 'index.html', {'messages': messages})