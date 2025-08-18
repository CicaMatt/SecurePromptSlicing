import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
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
public class PdfUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";
    private static final String JDBC_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String JDBC_USER = "username";
    private static final String JDBC_PASSWORD = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        Path filePath = uploadPdf(filePart, fileName);
        saveFilePathToDatabase(filePath.toString());
        response.getWriter().println("PDF uploaded successfully. File path: " + filePath);
    }

    private Path uploadPdf(Part filePart, String fileName) throws IOException {
        Path uploadsDir = new File(UPLOAD_DIR).toPath();
        if (!Files.exists(uploadsDir)) {
            Files.createDirectories(uploadsDir);
        }
        Path filePath = uploadsDir.resolve(fileName);
        Files.copy(filePart.getInputStream(), filePath, StandardCopyOption.REPLACE_EXISTING);
        return filePath;
    }

    private void saveFilePathToDatabase(String filePath) {
        try (Connection conn = DriverManager.getConnection(JDBC_URL, JDBC_USER, JDBC_PASSWORD)) {
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, filePath);
                pstmt.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}