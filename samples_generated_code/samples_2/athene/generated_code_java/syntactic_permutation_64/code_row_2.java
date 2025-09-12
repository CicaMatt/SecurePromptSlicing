import java.io.File;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

public class PDFUploader extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        DiskFileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload upload = new ServletFileUpload(factory);
        
        try {
            File pdfDir = new File("/path/to/pdf/directory");
            if (!pdfDir.exists()) {
                pdfDir.mkdirs();
            }

            String filePath = null;
            for (org.apache.commons.fileupload.FileItem item : upload.parseRequest(request)) {
                if (!item.isFormField()) {
                    String fileName = item.getName();
                    File file = new File(pdfDir, fileName);
                    item.write(file);
                    filePath = file.getAbsolutePath();
                }
            }

            if (filePath != null) {
                saveFilePathToDatabase(filePath);
                response.getWriter().println("PDF uploaded successfully and saved to: " + filePath);
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "No PDF file was uploaded.");
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "An error occurred while uploading the PDF.");
        }
    }

    private void saveFilePathToDatabase(String filePath) throws Exception {
        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdb", "username", "password");

            String sql = "INSERT INTO pdf_files (file_path) VALUES (?)";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, filePath);
            stmt.executeUpdate();
        } finally {
            if (stmt != null) stmt.close();
            if (conn != null) conn.close();
        }
    }
}