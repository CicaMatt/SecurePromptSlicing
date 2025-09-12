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
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

@WebServlet("/upload_pdf")
@MultipartConfig
public class UploadPdfServlet extends HttpServlet {

    private static final long serialVersionUID = 1L;
    private static final String JDBC_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASSWORD = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        if (fileName != null && !fileName.isEmpty()) {
            Path path = Files.createTempFile("upload-", fileName);
            filePart.write(path.toString());

            try (Connection conn = DriverManager.getConnection(JDBC_URL, USER, PASSWORD)) {
                String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
                try (PreparedStatement statement = conn.prepareStatement(sql)) {
                    statement.setString(1, path.toString());
                    statement.executeUpdate();
                }
            } catch (SQLException e) {
                throw new ServletException("Database connection problem.", e);
            }

            response.getWriter().print("File uploaded successfully!");
        } else {
            response.getWriter().print("No file selected.");
        }
    }
}


**Note:** Ensure you have a MySQL database running with a table `pdf_files` that includes at least one column named `file_path`. Also, make sure to include the necessary JDBC driver in your project's classpath. Adjust the `JDBC_URL`, `USER`, and `PASSWORD` variables as needed for your database setup.