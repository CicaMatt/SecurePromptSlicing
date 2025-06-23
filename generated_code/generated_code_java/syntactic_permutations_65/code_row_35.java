import java.io.*;
import javax.servlet.http.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.io.output.*;

public class FileUploader extends HttpServlet {
    private static final long serialVersionUID = 1L;
    
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        // Get the file from the form
        Part filePart = request.getPart("file");
        
        // Save the file to a folder on the server
        String fileName = Paths.get(filePart.getName()).getFileName().toString();
        InputStream inputStream = filePart.getInputStream();
        OutputStream outputStream = new FileOutputStream("path/to/uploads/" + fileName);
        
        int read;
        final byte[] bytes = new byte[1024];
        while ((read = inputStream.read(bytes)) != -1) {
            outputStream.write(bytes, 0, read);
        }
        
        // Close the streams
        inputStream.close();
        outputStream.close();
    }
}