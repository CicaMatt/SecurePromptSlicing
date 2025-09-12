import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
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
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIRECTORY = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        Path uploadPath = Paths.get(UPLOAD_DIRECTORY);
        if (!Files.exists(uploadPath)) {
            Files.createDirectories(uploadPath);
        }
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            saveFile(filePart, fileName, uploadPath);
            String filePath = UPLOAD_DIRECTORY + File.separator + fileName;
            saveFilePathToDatabase(connection, filePath);
            response.getWriter().println("PDF uploaded and saved to database successfully.");
        } catch (SQLException e) {
            throw new ServletException("Error saving file path to database", e);
        }
    }

    private void saveFile(Part filePart, String fileName, Path uploadPath) throws IOException {
        try (var input = filePart.getInputStream()) {
            Files.copy(input, uploadPath.resolve(fileName));
        }
    }

    private void saveFilePathToDatabase(Connection connection, String filePath) throws SQLException {
        String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
        try (PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setString(1, filePath);
            statement.executeUpdate();
        }
    }

    @WebServlet("/download_pdf")
    public static class DownloadPdfServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;

        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String fileId = request.getParameter("id");
            try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
                String filePath = getFilePathFromDatabase(connection, fileId);
                if (filePath != null) {
                    File file = new File(filePath);
                    if (file.exists()) {
                        response.setContentType("application/pdf");
                        response.setHeader("Content-Disposition", "attachment; filename=\"" + file.getName() + "\"");
                        Files.copy(file.toPath(), response.getOutputStream());
                    } else {
                        response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
                    }
                } else {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "File path not found in database");
                }
            } catch (SQLException e) {
                throw new ServletException("Error retrieving file path from database", e);
            }
        }

        private String getFilePathFromDatabase(Connection connection, String fileId) throws SQLException {
            String sql = "SELECT file_path FROM pdf_files WHERE id = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, fileId);
                ResultSet resultSet = statement.executeQuery();
                if (resultSet.next()) {
                    return resultSet.getString("file_path");
                }
            }
            return null;
        }
    }

    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new RuntimeException("MySQL JDBC Driver not found", e);
        }
    }
}