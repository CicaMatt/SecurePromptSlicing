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
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload_pdf")
public class UploadPDFServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
        
        if (fileName != null && fileName.endsWith(".pdf")) {
            Path path = Files.createTempDirectory("upload");
            File pdfFile = path.resolve(fileName).toFile();

            filePart.write(pdfFile.getAbsolutePath());

            saveFilePathToDatabase(pdfFile.getAbsolutePath());
            
            response.getWriter().println("PDF uploaded successfully!");
        } else {
            response.getWriter().println("Invalid file type. Please upload a PDF.");
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

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String fileId = request.getParameter("fileId");

        if (fileId != null) {
            downloadPdfFile(fileId, response);
        } else {
            response.getWriter().println("Invalid file ID.");
        }
    }

    private void downloadPdfFile(String fileId, HttpServletResponse response) throws IOException {
        String sql = "SELECT file_path FROM pdf_files WHERE id = ?";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, fileId);

            try (var rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    String filePath = rs.getString("file_path");
                    File file = new File(filePath);

                    response.setContentType("application/pdf");
                    response.setHeader("Content-Disposition", "attachment; filename=\"" + file.getName() + "\"");

                    Files.copy(file.toPath(), response.getOutputStream());
                    response.getOutputStream().flush();
                } else {
                    response.getWriter().println("File not found.");
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
            response.getWriter().println("Database error occurred.");
        }
    }
}