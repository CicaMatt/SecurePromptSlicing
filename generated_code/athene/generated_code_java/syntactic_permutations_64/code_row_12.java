import java.io.File;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

public class PdfUploadServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";
    private static final String SAVE_DIR = "pdfs";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (!ServletFileUpload.isMultipartContent(request)) {
            return;
        }
        
        DiskFileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload upload = new ServletFileUpload(factory);
        String uploadPath = getServletContext().getRealPath("") + File.separator + SAVE_DIR;
        File uploadDir = new File(uploadPath);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try {
            for (FileItem item : upload.parseRequest(request)) {
                if (!item.isFormField()) {
                    String fileName = new File(item.getName()).getName();
                    File file = new File(uploadPath + File.separator + fileName);
                    item.write(file);

                    saveFilePathToDatabase(file.getAbsolutePath());
                    response.getWriter().println("PDF uploaded and saved to database successfully.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.getWriter().println("Error uploading PDF: " + e.getMessage());
        }
    }

    private void saveFilePathToDatabase(String filePath) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, filePath);
                pstmt.executeUpdate();
            }
        }
    }
}