import java.io.File;
import java.io.FileOutputStream;
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
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/uploadPdf")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, maxFileSize = 1024 * 1024 * 10, maxRequestSize = 1024 * 1024 * 50)
public class UploadPdfServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        if (filePart != null && filePart.getSubmittedFileName().endsWith(".pdf")) {
            String uploadsDir = "/uploads/";
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
            Path filePath = Paths.get(request.getServletContext().getRealPath(uploadsDir) + fileName);

            try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
                byte[] fileContent = filePart.getInputStream().readAllBytes();
                fos.write(fileContent);
            }

            saveFilePathToDatabase(filePath.toString());
        }
    }

    private void saveFilePathToDatabase(String filePath) {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, filePath);
            pstmt.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws ServletException, IOException {
        // This is just for testing purposes. In a real application, you would deploy this servlet in a web container.
        javax.servlet.UnavailableException exception = new javax.servlet.UnavailableException("Servlet not started.");
        throw exception;
    }
}


**Note:** Ensure your MySQL database and table `pdf_files` are properly set up with at least one column named `file_path`. Adjust the database URL, user, and password as necessary. This code assumes a servlet container is used for deployment.