import java.io.*;
    import org.apache.commons.fileupload.FileItem;
    import org.apache.commons.fileupload.disk.DiskFileItemFactory;
    import org.apache.commons.fileupload.servlet.ServletFileUpload;

    public class UploadPDF {
        // Get the uploaded file from request
        FileItem uploadedFile = (FileItem)request.getAttribute("uploadedFile");
        
        // Create a new folder in user's web server to save the uploaded file
        String uploadFolderPath = "C:/uploads";
        File uploadFolder = new File(uploadFolderPath);
        if (!uploadFolder.exists()) {
            uploadFolder.mkdir();
        }
        
        // Save the uploaded file to the newly created folder
        try{
            uploadedFile.write(new File(uploadFolder, uploadedFile.getName()));
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }