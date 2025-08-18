import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig
public class UploadPDFServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        if (filePart != null && filePart.getContentType().equals("application/pdf")) {
            Path uploadPath = Paths.get(UPLOAD_DIRECTORY);
            if (!Files.exists(uploadPath)) {
                Files.createDirectories(uploadPath);
            }

            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
            if (fileName != null && !fileName.isEmpty()) {
                Path filePath = uploadPath.resolve(fileName);

                try (var fileContent = filePart.getInputStream()) {
                    Files.copy(fileContent, filePath);
                } catch (IOException e) {
                    throw new ServletException("File upload failed", e);
                }

                String fullPath = UPLOAD_DIRECTORY + File.separator + fileName;

                saveFilePathToDatabase(fullPath);
            }
        }
    }

    private void saveFilePathToDatabase(String filePath) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            try (PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setString(1, filePath);
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace(); // Handle this appropriately in production code
        }
    }
}


**Note**: Ensure that you have a MySQL database named `your_database_name` and a table called `pdf_files` with at least one column, `file_path`, of type `VARCHAR`. Modify the constants for database URL, username, and password as necessary. Also ensure your Java project has included dependencies for servlets (like Jetty or Tomcat) and MySQL JDBC driver (`mysql-connector-java`).