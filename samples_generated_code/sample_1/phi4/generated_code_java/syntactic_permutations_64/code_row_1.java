import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig
public class UploadPdfServlet extends HttpServlet {
    private static final String UPLOAD_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        if (filePart != null && filePart.getSubmittedFileName().toLowerCase().endsWith(".pdf")) {
            Path uploadsDir = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
            try {
                Files.createDirectories(uploadsDir);

                String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
                if (fileName != null) {
                    Path filePath = uploadsDir.resolve(fileName);
                    filePart.write(filePath.toString());

                    saveFilePathToDatabase(fileName, response);
                }
            } catch (Exception e) {
                throw new ServletException("File upload failed", e);
            }
        }
    }

    private void saveFilePathToDatabase(String fileName, HttpServletResponse response) throws IOException {
        String filePath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY + File.separator + fileName).toString();
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO pdf_files (file_path) VALUES (?)")) {

            stmt.setString(1, filePath);
            stmt.executeUpdate();

            response.getWriter().write("File uploaded and saved successfully!");
        } catch (Exception e) {
            throw new IOException("Database operation failed", e);
        }
    }

    public void destroy() {
        // Close database connection
    }
}