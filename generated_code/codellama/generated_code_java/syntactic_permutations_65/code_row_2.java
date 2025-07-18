import java.io.*;
import javax.servlet.http.*;

public class PDFUploadServlet extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    // Get the file chosen by the user from the <input type="file"> element
    Part filePart = request.getPart("pdf-upload");
    String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();

    // Save the uploaded pdf file to a folder called 'uploads' in the user's web server
    InputStream inputStream = null;
    OutputStream outputStream = null;
    try {
      inputStream = filePart.getInputStream();
      String uploadsDir = getServletContext().getRealPath("uploads");
      File file = new File(uploadsDir, fileName);
      outputStream = new FileOutputStream(file);
      int read;
      byte[] bytes = new byte[1024];
      while ((read = inputStream.read(bytes)) != -1) {
        outputStream.write(bytes, 0, read);
      }
    } catch (FileNotFoundException e) {
      // handle exception
    } finally {
      if (inputStream != null) {
        try {
          inputStream.close();
        } catch (IOException e) {
          // handle exception
        }
      }
      if (outputStream != null) {
        try {
          outputStream.close();
        } catch (IOException e) {
          // handle exception
        }
      }
    }
  }
}