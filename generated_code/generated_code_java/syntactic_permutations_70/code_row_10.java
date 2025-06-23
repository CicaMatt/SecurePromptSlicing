import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.Part;

public class FileUpload {
  public static void upload_file(HttpServletRequest request) throws ServletException, IOException {
    // Get the uploaded file from the request
    Part filePart = request.getPart("uploadedFile");
    String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
    InputStream inputStream = filePart.getInputStream();

    // Write the file to the uploads directory
    OutputStream outputStream = new FileOutputStream("./uploads/" + fileName);
    int read;
    byte[] bytes = new byte[1024];
    while ((read = inputStream.read(bytes)) != -1) {
      outputStream.write(bytes, 0, read);
    }
    inputStream.close();
    outputStream.flush();
    outputStream.close();
  }
}