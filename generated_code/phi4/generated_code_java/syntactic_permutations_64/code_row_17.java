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

@MultipartConfig(fileSizeThreshold = 1024 * 1024, maxFileSize = 1024 * 1024 * 10, maxRequestSize = 1024 * 1024 * 50)
public class UploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        if (fileName != null && !fileName.isEmpty()) {
            Path uploadPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);
            
            if (!Files.exists(uploadPath)) {
                Files.createDirectories(uploadPath);
            }

            try (var fileContent = filePart.getInputStream()) {
                String filePath = uploadPath.resolve(fileName).toString();
                
                // Save the uploaded PDF to the server
                Files.copy(fileContent, Paths.get(filePath));

                // Store the filepath in MySQL database
                saveFilePathToDatabase(filePath);

                response.getWriter().print("File uploaded and saved successfully.");
            } catch (IOException | SQLException e) {
                throw new ServletException("File upload failed", e);
            }
        } else {
            response.getWriter().print("No file was uploaded.");
        }
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO your_table_name (file_path) VALUES (?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, filePath);
                statement.executeUpdate();
            }
        }
    }

    public static void main(String[] args) {
        // This is a simple way to test the servlet if you're running it standalone.
        // It's recommended to configure this in a web container like Tomcat for production use.
        System.out.println("UploadServlet ready. Deploy and run on a server.");
    }
}


**Note:** Replace `your_database_name`, `your_username`, `your_password`, and `your_table_name` with your actual database details. Make sure to have the MySQL JDBC driver in your classpath if running this standalone or deployed.