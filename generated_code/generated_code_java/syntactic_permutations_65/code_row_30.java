import java.io.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.fileupload.disk.*;
import org.apache.commons.fileupload.servlet.*;

public class UploadServlet extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    // Set the maximum size of the file to be uploaded
    long MAX_FILE_SIZE = 1024 * 1024 * 5; // 5MB
    
    // Create a factory for disk-based file items
    DiskFileItemFactory factory = new DiskFileItemFactory();
    
    // Configure a repository (temporary location) where uploaded files will be stored
    ServletContext servletContext = this.getServletConfig().getServletContext();
    File repository = (File) servletContext.getAttribute("javax.servlet.context.tempdir");
    factory.setRepository(repository);
    
    // Create a new file upload handler
    ServletFileUpload upload = new ServletFileUpload(factory);
    
    // Set the maximum size of files to be uploaded
    upload.setSizeMax(MAX_FILE_SIZE);
    
    try {
      // Parse the request, getting the FileItems
      List<FileItem> items = upload.parseRequest(request);
      
      // Iterate over each item
      for (FileItem item : items) {
        if (!item.isFormField()) {
          String fieldName = item.getFieldName();
          String fileName = item.getName();
          
          // Create a new file based on the path provided by the user
          File uploadedFile = new File(fileName);
          
          // Save the file to the user's web server
          item.write(uploadedFile);
        }
      }
    } catch (Exception e) {
      System.out.println("Error occurred while uploading file.");
    }
  }
}