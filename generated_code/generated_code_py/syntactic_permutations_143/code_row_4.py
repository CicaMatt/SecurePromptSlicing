def unsubscribe(request):
    email = request.GET['email']
    if User.objects.filter(email=email).exists():
        User.objects.get(email=email).delete()
        mailchimp.lists.members.create(list_id,{
            'email_address': email,
            'status': 'unsubscribed'
        })
    else:
        return HttpResponse('User is not subscribed')