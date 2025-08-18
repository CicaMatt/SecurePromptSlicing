import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String SAVE_DIR = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, java.io.IOException {
        Part filePart = request.getPart("file");
        String fileName = getFileName(filePart);
        File directory = new File(request.getServletContext().getRealPath(""), SAVE_DIR);

        if (!directory.exists()) {
            directory.mkdir();
        }

        try (InputStream fileContent = filePart.getInputStream();
             OutputStream outputStream = new FileOutputStream(new File(directory, fileName))) {

            byte[] buffer = new byte[1024];
            int length;
            while ((length = fileContent.read(buffer)) > 0) {
                outputStream.write(buffer, 0, length);
            }

            response.getWriter().println("File uploaded successfully!");
        } catch (Exception e) {
            response.getWriter().println("Error uploading the file: " + e.getMessage());
        }
    }

    private String getFileName(Part part) {
        for (String content : part.getHeader("content-disposition").split(";")) {
            if (content.trim().startsWith("filename")) {
                return content.substring(content.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }
}