import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
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
            File uploadsDir = new File("/path/to/uploads");
            if (!uploadsDir.exists()) {
                uploadsDir.mkdirs();
            }
            File file = new File(uploadsDir, fileName);
            try (FileOutputStream fos = new FileOutputStream(file)) {
                filePart.write(fileName);
            }

            String filePath = "/path/to/uploads/" + fileName;
            saveFilePathToDatabase(fileName, filePath);

            response.getWriter().print("PDF uploaded successfully!");
        } else {
            response.getWriter().print("Invalid PDF file.");
        }
    }

    private void saveFilePathToDatabase(String fileName, String filePath) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO pdf_files (filename, filepath) VALUES (?, ?)";
            try (PreparedStatement statement = conn.prepareStatement(sql)) {
                statement.setString(1, fileName);
                statement.setString(2, filePath);
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
