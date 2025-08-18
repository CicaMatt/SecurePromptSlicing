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
public class UploadPdfServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String DB_USER = "your_db_user";
    private static final String DB_PASSWORD = "your_db_password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");

        // Get the file part from the request
        Part filePart = request.getPart("pdfFile");
        if (filePart != null) {
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
            Path uploadPath = Paths.get(getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY);

            // Create the directory if it does not exist
            if (!Files.exists(uploadPath)) {
                Files.createDirectories(uploadPath);
            }

            // Save the file on disk
            try (var outputStream = new java.io.FileOutputStream(uploadPath.resolve(fileName).toString())) {
                filePart.write(outputStream);
            } catch (IOException e) {
                throw new ServletException("Failed to write PDF file", e);
            }

            String filePath = uploadPath.resolve(fileName).toString();

            // Save the file path in the database
            try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
                String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
                try (PreparedStatement statement = connection.prepareStatement(sql)) {
                    statement.setString(1, filePath);
                    statement.executeUpdate();
                }
            } catch (SQLException e) {
                throw new ServletException("Database error", e);
            }

            response.getWriter().println("PDF uploaded successfully!");
        } else {
            response.getWriter().println("No file uploaded.");
        }
    }
}


Make sure to replace `your_database_name`, `your_db_user`, and `your_db_password` with your actual database credentials. Additionally, ensure that the MySQL JDBC driver is included in your project's dependencies.