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

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024 * 10, // 10 MB
        maxFileSize = 1024 * 1024 * 50,      // 50 MB
        maxRequestSize = 1024 * 1024 * 100)   // 100 MB
public class PDFUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String UPLOAD_DIR = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String DB_USER = "your_db_user";
    private static final String DB_PASSWORD = "your_db_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        String uploadPath = getServletContext().getRealPath("") + File.separator + UPLOAD_DIR;
        Path uploadFilePath = Paths.get(uploadPath + File.separator + fileName);

        try {
            Files.createDirectories(Paths.get(uploadPath));
            filePart.write(uploadFilePath.toString());

            saveFilePathToDatabase(uploadFilePath.toString());
        } catch (IOException | SQLException e) {
            response.getWriter().println("File upload failed: " + e.getMessage());
        }
    }

    private void saveFilePathToDatabase(String filePath) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "INSERT INTO pdf_files (filepath) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, filePath);
                pstmt.executeUpdate();
            }
        }
    }

    @WebServlet("/download")
    public static class PDFDownloadServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;

        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            int fileId = Integer.parseInt(request.getParameter("id"));

            try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
                String sql = "SELECT filepath FROM pdf_files WHERE id = ?";
                try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                    pstmt.setInt(1, fileId);
                    try (ResultSet rs = pstmt.executeQuery()) {
                        if (rs.next()) {
                            String filePath = rs.getString("filepath");
                            File file = new File(filePath);

                            response.setContentType("application/pdf");
                            response.addHeader("Content-Disposition", "attachment; filename=" + file.getName());
                            Files.copy(file.toPath(), response.getOutputStream());
                        } else {
                            response.getWriter().println("File not found.");
                        }
                    }
                }
            } catch (SQLException e) {
                response.getWriter().println("Error downloading file: " + e.getMessage());
            }
        }
    }

    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}