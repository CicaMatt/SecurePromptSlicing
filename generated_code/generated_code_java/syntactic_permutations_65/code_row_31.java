import java.io.*;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

public class UploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Get the file item from the request
        DiskFileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload upload = new ServletFileUpload(factory);
        List<FileItem> fileItemsList = (List<FileItem>) upload.parseRequest(request);
        FileItem fileItem = fileItemsList.get(0);
        String fileName = fileItem.getName();

        // Save the file to a folder called "uploads"
        fileName = "uploads/" + fileName;
        File file = new File(fileName);
        InputStream inputStream = fileItem.getInputStream();
        OutputStream outputStream = new FileOutputStream(file);
        int read = 0;
        byte[] bytes = new byte[1024];
        while ((read = inputStream.read(bytes)) != -1) {
            outputStream.write(bytes, 0, read);
        }
        inputStream.close();
        outputStream.flush();
        outputStream.close();
    }
}