import java.io.*;
import org.apache.commons.fileupload.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
import com.itextpdf.text.Document;
import com.itextpdf.text.DocumentException;
import com.itextpdf.text.Paragraph;
import com.itextpdf.text.pdf.PdfWriter;
import javax.servlet.annotation.*;

@WebServlet(urlPatterns = {"/upload"})
public class Upload extends HttpServlet {

   @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException 
    {
        int maxFileSize = 5000 * 1024;
        int maxMemSize = 5000 * 1024;
        File file ;
        
        try{
            // checks if the request actually contains upload file
            if(!ServletFileUpload.isMultipartContent(request)){
                throw new RuntimeException("request does not contain a multipart/form-data or multipart/mixed stream, content type header is " + request.getHeader("content-type"));
            }
            
            // configures upload settings
            DiskFileItemFactory factory = new DiskFileItemFactory();
            factory.setSizeThreshold(maxMemSize);
            File repository = (File) getServletContext().getAttribute("javax.servlet.context.tempdir");
            factory.setRepository(repository);
            
            // constructs the folder where uploaded file will be stored
            ServletFileUpload upload = new ServletFileUpload(factory);
            upload.setSizeMax( maxFileSize );
            
            String uploadPath = getServletContext().getRealPath("./") + File.separator + "uploads" + File.separator;
            
            // creates the directory if it does not exist
            File uploadDir = new File(uploadPath);
            if(!uploadDir.exists()){
                uploadDir.mkdir();
            }
            
            List<FileItem> formItems = upload.parseRequest(request);
            
            if (formItems != null && formItems.size() > 0) {
                // iterates over form's fields
                for (FileItem item : formItems) {
                    // processes only fields that are not form fields
                    if (!item.isFormField()) {
                        String fileName = new File(item.getName()).getName();
                        String filePath = uploadPath + File.separator + fileName;
                        
                        File storeFile = new File(filePath);
                        // saves the file on disk
                        item.write(storeFile);
                    }
                }
            }
            
            response.sendRedirect("index.jsp");
            
        } catch (Exception ex) {
            request.setAttribute("message", "File Upload Failed due to " + ex);
        }
        
    }
    
}