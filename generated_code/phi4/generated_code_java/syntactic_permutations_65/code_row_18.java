import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create uploads directory if it does not exist
        String applicationPath = getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdirs();
        }

        for (Part part : request.getParts()) {
            String fileName = Paths.get(part.getSubmittedFileName()).getFileName().toString(); // MSIE fix.

            if (fileName != null && !fileName.isEmpty() && fileName.endsWith(".pdf")) {
                Path filePath = Paths.get(uploadFilePath + File.separator + fileName);

                try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
                    fos.write(part.getInputStream().readAllBytes());
                }
            }
        }

        response.getWriter().print("PDF file uploaded successfully");
    }
}


Ensure that your web application is configured properly to handle multipart requests, and the `web.xml` is set up correctly if you are not using annotations for servlet configuration. Also, ensure your server has the required permissions to write files in the specified directory.