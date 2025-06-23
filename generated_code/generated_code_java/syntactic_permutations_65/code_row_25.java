import java.io.*;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.Part;

@MultipartConfig(maxFileSize = 16177215) public class UploadServlet extends HttpServlet {
    @Override protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Get the file chosen by the user.
        Part filePart = request.getPart("file");
        String fileName = getFileName(filePart);
        InputStream inputStream = null;
        OutputStream outputStream = null;
        try {
            inputStream = filePart.getInputStream();
            File newFile = new File("C:\\Users\\Public\\Documents\\uploads\\" + fileName);
            if (!newFile.exists()) {
                boolean created = newFile.createNewFile();
            }
            outputStream = new FileOutputStream(newFile);
            int read = 0;
            final byte[] bytes = new byte[1024];
            while ((read = inputStream.read(bytes)) != -1) {
                outputStream.write(bytes, 0, read);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (outputStream != null) {
                try {
                    outputStream.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if (inputStream != null) {
                inputStream.close();
            }
        }
    }
    private static String getFileName(final Part part) {
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(content.lastIndexOf("=")).replaceAll("\"", "");
            }
        }
        return null;
    }
}