from django.http import FileResponse
    from django.shortcuts import get_object_or_404
    
    def image_view(request, filename):
        img = get_object_or_404(Image, file=filename)
        return FileResponse(open('images/' + img.file.name, 'rb'))