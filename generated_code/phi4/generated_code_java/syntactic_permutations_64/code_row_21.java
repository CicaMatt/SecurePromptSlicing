import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, maxFileSize = 1024 * 1024 * 10, maxRequestSize = 1024 * 1024 * 50)
public class UploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        if (filePart != null && filePart.getSubmittedFileName().endsWith(".pdf")) {
            Path uploadsDir = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
            Files.createDirectories(uploadsDir);

            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
            if (fileName != null) {
                Path filePath = uploadsDir.resolve(fileName);
                try (var fileContent = filePart.getInputStream()) {
                    Files.copy(fileContent, filePath);
                }

                // Save the filepath in a session attribute or database as needed
                request.getSession().setAttribute("pdfFilePath", UPLOAD_DIRECTORY + File.separator + fileName);

                response.getWriter().write("File uploaded successfully!");
            } else {
                response.getWriter().write("Invalid file name.");
            }
        } else {
            response.getWriter().write("Please upload a PDF file.");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String filePath = (String) request.getSession().getAttribute("pdfFilePath");
        if (filePath != null) {
            Path pathToFile = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY + File.separator + filePath);
            if (Files.exists(pathToFile)) {
                response.setContentType("application/pdf");
                response.setHeader("Content-Disposition", "attachment; filename=\"" + pathToFile.getFileName() + "\"");

                Files.copy(pathToFile, response.getOutputStream());
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found.");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "No file path specified.");
        }
    }
}