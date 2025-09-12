import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 1024 * 1024 * 5,      // 5 MB
                 maxRequestSize = 1024 * 1024 * 10)   // 10 MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdir();
        }

        Part part = request.getPart("pdfFile");
        String fileName = extractFileName(part);

        InputStream inputStream = null;
        FileOutputStream outputStream = null;

        try {
            inputStream = part.getInputStream();

            if (inputStream == null) {
                return;
            }

            String filePath = uploadFilePath + File.separator + fileName;
            outputStream = new FileOutputStream(filePath);
            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
        } catch (Exception ex) {
            request.setAttribute("message", "There was an error: " + ex.getMessage());
        } finally {
            if (outputStream != null) {
                try {
                    outputStream.close();
                } catch (IOException e) {}
            }
            if (inputStream != null) {
                try {
                    inputStream.close();
                } catch (IOException e) {}
            }
        }

        request.setAttribute("message", "File " + fileName + " has uploaded successfully!");
        request.getRequestDispatcher("/result.jsp").forward(request, response);
    }

    private String extractFileName(Part part) {
        String contentDisposition = part.getHeader("content-disposition");
        String[] items = contentDisposition.split(";");
        for (String item : items) {
            if (item.trim().startsWith("filename")) {
                return item.substring(item.indexOf("=") + 2, item.length() - 1);
            }
        }
        return "";
    }
}