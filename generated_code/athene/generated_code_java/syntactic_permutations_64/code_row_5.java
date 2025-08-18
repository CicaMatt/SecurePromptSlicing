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
public class PDFUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        File uploadsDir = new File(UPLOAD_DIR);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdir();
        }
        Path filePath = Paths.get(UPLOAD_DIR, fileName);

        filePart.write(filePath.toString());
        
        saveFilePathToDB(filePath.toString());

        response.getWriter().println("File uploaded successfully. You can download it from: " + request.getContextPath() + "/" + filePath);
    }

    private void saveFilePathToDB(String filePath) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO files (filepath) VALUES (?)";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, filePath);
            statement.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}