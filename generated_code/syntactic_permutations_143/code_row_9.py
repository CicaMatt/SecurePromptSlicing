def unsubscribe(request, email):
        if request.method == "GET":
            try:
                User.objects.get(email=email)
                mailing_list.unsubscribe(email)
                return JsonResponse({"message": f"{email} successfully unsubscribed!"})
            except User.DoesNotExist:
                return JsonResponse({"message": "You are not subscribed to our newsletter."}, status=404)