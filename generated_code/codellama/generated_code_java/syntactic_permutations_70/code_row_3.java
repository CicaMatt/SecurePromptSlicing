import javax.servlet.ServletException;
    import java.io.*;
    import org.apache.commons.fileupload.*;
    import org.apache.commons.fileupload.disk.*;
    import org.apache.commons.fileupload.servlet.*;
    import java.util.*;
    import java.sql.*;
    
    public class upload extends HttpServlet {
      private static final int MAX_MEMORY_SIZE = 1024 * 1024 * 5; // 5MB
      private static final int MAX_UPLOAD_FILE_SIZE = 1024 * 1024 * 10; // 10MB
    
      protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        
        DiskFileItemFactory factory = new DiskFileItemFactory();
        File repository = (File) getServletContext().getAttribute("javax.servlet.context.tempdir");
        factory.setRepository(repository);
        ServletFileUpload upload = new ServletFileUpload(factory);
        
        try {
          List<FileItem> fields = upload.parseRequest(request);
          Iterator<FileItem> itr = fields.iterator();
          
          while (itr.hasNext()) {
            FileItem item = itr.next();
            
            if (!item.isFormField()) {
              String fileName = item.getName();
              fileName = new Date().getTime() + "_" + fileName;
              
              File file = new File(request.getServletContext().getAttribute("uploads").toString(), fileName);
              item.write(file);
            }
          }
        } catch (FileUploadException e) {
          throw new ServletException();
        }
        
        out.println("<html><body>");
        out.println("Your file has been uploaded.");
        out.println("</body></html>");
      }
    }