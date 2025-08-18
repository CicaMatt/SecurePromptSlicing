import java.io.File;
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
@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String DESTINATION_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = getFileName(filePart);
        InputStream fileContent = filePart.getInputStream();

        File destinationDir = new File(DESTINATION_DIR);
        if (!destinationDir.exists()) {
            destinationDir.mkdirs();
        }

        File targetFile = new File(destinationDir, fileName);
        try (InputStream in = fileContent) {
            java.nio.file.Files.copy(in, targetFile.toPath());
        }

        response.getWriter().println("File uploaded successfully: " + fileName);
    }

    private String getFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return "unnamed";
    }
}