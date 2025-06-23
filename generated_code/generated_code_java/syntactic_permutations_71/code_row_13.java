import java.io.File;  
import java.util.*;  
import org.apache.commons.fileupload.*;  
import org.apache.commons.fileupload.disk.*;  
import org.apache.commons.fileupload.servlet.*;  
import javax.servlet.http.HttpServletRequest;  
import org.apache.commons.io.FilenameUtils;

public class UploadServlet extends HttpServlet {
  private static final String DATA_DIRECTORY = "uploadedFiles";
  private static final long serialVersionUID = 1L;
    
  @Override
  protected void doPost(HttpServletRequest req) throws ServletException, IOException {  
    System.out.println("UploadServlet.doPost()");
      
    DiskFileItemFactory factory = new DiskFileItemFactory();
    factory.setSizeThreshold(1024 * 1024);
    File tempDir = (File) getServletContext().getAttribute("javax.servlet.context.tempdir");
    factory.setRepository(tempDir);
      
    ServletFileUpload upload = new ServletFileUpload(factory);
      
    try {  
      List<FileItem> items = upload.parseRequest(req);
      Iterator<FileItem> iterator = items.iterator();
          
      while (iterator.hasNext()) {
        FileItem item = iterator.next();
        if (!item.isFormField()) {
          String name = new File(item.getName()).getName();
          item.write(new File(DATA_DIRECTORY + File.separator + name));
        }
      }  
    } catch (FileUploadException e) {  
      System.out.println("Error encountered while parsing the request");
    } catch (Exception e) {  
      System.out.println("Error encountered while uploading file");
    }  
  }
}