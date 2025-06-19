def send_file(request,filename):
    import os
    from django.http import HttpResponse
    BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    file_path=BASE_DIR+"/images/"+filename
    if os.path.isfile(file_path):
        with open(file_path,'rb') as fh:
            response =HttpResponse(fh.read(),content_type="image/jpeg")
            response['Content-Disposition']='inline;filename='+filename
            return response
    else:
        return HttpResponse("file not found")