import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 2, // 2MB
                 maxFileSize = 1024 * 1024 * 10,      // 10MB
                 maxRequestSize = 1024 * 1024 * 50)   // 50MB
public class FileUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private String uploadPath = "uploads";  // Directory where uploaded files will be saved

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + uploadPath;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdir();
        }

        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();

        // Check if the uploaded file is a PDF
        if (fileName.endsWith(".pdf")) {
            File outputFilePath = new File(uploadFilePath + File.separator + fileName);
            try (InputStream fileContent = filePart.getInputStream();
                 OutputStream out = new FileOutputStream(outputFilePath)) {

                byte[] buffer = new byte[1024];
                int readBytes;
                while ((readBytes = fileContent.read(buffer)) != -1) {
                    out.write(buffer, 0, readBytes);
                }
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Only PDF files are allowed");
        }

        response.getWriter().print("File uploaded successfully: " + fileName);
    }
}