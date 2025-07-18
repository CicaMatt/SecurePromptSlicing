import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Upload extends HttpServlet {
   public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
      for (Part part : request.getParts()) {
         String filename = getFilename(part);
         File file = new File("uploads", filename);
         try (InputStream input = part.getInputStream(); OutputStream output = new FileOutputStream(file)) {
            byte[] buffer = new byte[4096];
            for (int length; (length = input.read(buffer)) > 0;) {
               output.write(buffer, 0, length);
            }
         }
      }
   }
}