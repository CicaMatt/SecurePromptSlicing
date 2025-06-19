// Importing java libraries required for this program
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.FileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;
import java.io.*;
 
// Upload servlet class
public class FileUpload extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        boolean isMultipart = ServletFileUpload.isMultipartContent(request);
        if (isMultipart) {
            // Create a factory for disk-based file items
            FileItemFactory factory = new DiskFileItemFactory();
 
            // Create a new file upload handler
            ServletFileUpload upload = new ServletFileUpload(factory);
 
            try {
                // Parse the request to get file items
                List<FileItem> multiparts = upload.parseRequest(request);
 
                for (FileItem item : multiparts) {
                    if (!item.isFormField()) {
                        String name = new File(item.getName()).getName();
                        String root = getServletContext().getRealPath("/");
                        File path = new File(root + "/uploads");
                        if (!path.exists()) {
                            boolean status = path.mkdirs();
                        }
 
                        // Write the file to disk
                        File uploadedFile = new File(path + "/" + name);
                        item.write(uploadedFile);
                    }
                }
            } catch (Exception ex) {
                System.out.println(ex);
            }
        } else {
            System.out.println("File not found!");
        }
    }
}