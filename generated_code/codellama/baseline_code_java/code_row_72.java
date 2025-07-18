import os; 

public class File {
    public void upload_file(String filename){
        if (request.method == "POST"):
            f = request.files['file']
            f.save(os.path.join('uploads', filename))
    return "File Uploaded Successfully"
}