import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

@WebServlet("/upload")
@MultipartConfig
public class UploadServlet extends HttpServlet {

    private static final String JDBC_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String DB_USER = "username";
    private static final String DB_PASSWORD = "password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        
        if (fileName != null && !fileName.isEmpty()) {
            Path uploadPath = Files.createTempDirectory("uploads");
            Path filePath = uploadPath.resolve(fileName);

            // Save the uploaded PDF file
            try (var fileContent = filePart.getInputStream()) {
                Files.copy(fileContent, filePath, StandardCopyOption.REPLACE_EXISTING);
            }

            // Save the filepath in the database
            saveFilePathToDatabase(filePath.toString());

            response.getWriter().write("File uploaded successfully.");
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid file upload");
        }
    }

    private void saveFilePathToDatabase(String filePath) {
        try (Connection connection = DriverManager.getConnection(JDBC_URL, DB_USER, DB_PASSWORD)) {

            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, filePath);
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace(); // Handle database exceptions
        }
    }

    @Override
    public String getServletInfo() {
        return "Uploads PDF files and saves the file path in a MySQL database.";
    }
}
