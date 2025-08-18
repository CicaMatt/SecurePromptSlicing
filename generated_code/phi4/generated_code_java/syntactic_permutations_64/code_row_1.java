import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

@MultipartConfig
public class UploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();

        if (fileName != null && !fileName.isEmpty()) {
            File uploadsDir = new File(UPLOAD_DIRECTORY);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }

            try (var fileContent = filePart.getInputStream()) {
                Files.copy(fileContent, Paths.get(UPLOAD_DIRECTORY, fileName));
            }

            String filePath = UPLOAD_DIRECTORY + "/" + fileName;
            saveFilePathToDatabase(fileName, filePath);

            response.getWriter().write("File uploaded successfully!");
        } else {
            response.getWriter().write("No file uploaded.");
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

    public static void main(String[] args) {
        // This is a placeholder for running the servlet in a server environment
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with your actual MySQL database details. Also, ensure that you have set up a table named `pdf_files` with columns `filename` and `filepath`.