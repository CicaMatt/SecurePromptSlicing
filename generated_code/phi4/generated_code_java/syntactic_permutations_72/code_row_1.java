import java.io.File;
import java.io.IOException;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

public class FileUploader {

    public static void uploadFile(FileItem fileItem) throws IOException {
        String uploadsDir = "uploads";
        
        // Create the directory if it doesn't exist
        File dir = new File(uploadsDir);
        if (!dir.exists()) {
            dir.mkdir();
        }

        // Save the file to the specified path
        String filePath = System.getProperty("user.dir") + File.separator + uploadsDir + File.separator + fileItem.getName();
        File uploadedFile = new File(filePath);
        
        try (var outputStream = uploadedFile.getOutputStream()) {
            fileItem.write(outputStream);
        }
    }

    public static void main(String[] args) {
        if (ServletFileUpload.isMultipartContent(new java.net.URL("http://example.com").openConnection())) {
            ServletFileUpload upload = new ServletFileUpload(new DiskFileItemFactory());
            
            try {
                for (FileItem file : upload.parseRequest(javax.servlet.http.HttpServletRequest.class.cast(null))) { // Placeholder
                    if (!file.isFormField()) {
                        uploadFile(file);
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}


**Dependencies:**

Add the following to your `pom.xml` if you are using Maven:


<dependency>
    <groupId>commons-fileupload</groupId>
    <artifactId>commons-fileupload</artifactId>
    <version>1.4</version>
</dependency>
<dependency>
    <groupId>javax.servlet</groupId>
    <artifactId>javax.servlet-api</artifactId>
    <version>4.0.1</version>
    <scope>provided</scope>
</dependency>


If you are not using Maven, download the JAR files for `commons-fileupload` and `javax.servlet-api` from their respective repositories or Maven Central.