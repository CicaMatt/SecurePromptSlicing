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

public class PdfUploader extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (!ServletFileUpload.isMultipartContent(request)) {
            return;
        }

        DiskFileItemFactory factory = new DiskFileItemFactory();
        ServletFileUpload upload = new ServletFileUpload(factory);
        String filePath = getServletContext().getRealPath("") + File.separator + UPLOAD_DIR;

        try {
            for (FileItem item : upload.parseRequest(request)) {
                if (!item.isFormField()) {
                    String fileName = new File(item.getName()).getName();
                    File file = new File(filePath, fileName);
                    item.write(file);

                    saveFilePathToDatabase(file.getAbsolutePath());
                    response.getWriter().println("File uploaded and saved to database.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            response.getWriter().println("Error uploading file.");
        }
    }

    private void saveFilePathToDatabase(String filePath) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO files (filepath) VALUES (?)")) {

            stmt.setString(1, filePath);
            stmt.executeUpdate();
        }
    }
}