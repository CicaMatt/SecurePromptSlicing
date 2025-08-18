import java.io.File;
import java.io.FileOutputStream;
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

@WebServlet("/upload_pdf")
@MultipartConfig
public class UploadPdfServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        
        if (fileName != null && !fileName.isEmpty()) {
            File uploadsDir = new File("/path/to/uploads/folder");
            if (!uploadsDir.exists()) {
                uploadsDir.mkdirs();
            }
            
            Path filePath = Paths.get(uploadsDir.getAbsolutePath(), fileName);
            try (FileOutputStream fos = new FileOutputStream(filePath.toFile())) {
                filePart.write(fileName, fos);
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

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}