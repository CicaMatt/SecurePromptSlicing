import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class UploadServlet extends HttpServlet {
  @Override
  protected void doPost(HttpServletRequest request, 
                        HttpServletResponse response) throws ServletException, IOException {
    // Get the file chosen by the user.
    Part filePart = request.getPart("file");
    String fileName = getFileName(filePart);

    InputStream fileContent = filePart.getInputStream();
    
    // Write the file to a local file on your server. 
    File outputFile = new File("/path/to/outputdir", fileName);
    Files.copy(fileContent, outputFile.toPath());
  }

  private String getFileName(Part part) {
    for (String content : part.getHeader("content-disposition").split(";")) {
      if (content.trim().startsWith("filename")) {
        return content.substring(
            content.indexOf('=') + 1).trim().replace("\"", "");
      }
    }
    return null;
  }
}