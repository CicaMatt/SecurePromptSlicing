def img(request, name):
    f = open('images/' + name, 'rb')
    return HttpResponse(f.read(), content_type="image/jpeg")
  
@csrf_exempt
def img(request, name):
    f = open('images/' + name, 'rb')
    return HttpResponse(f.read(), content_type="image/jpeg")
  
urlpatterns = [
    path('img/<str:name>', views.img),
]