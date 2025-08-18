import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload_pdf")
@MultipartConfig
public class PDFUploadServlet extends HttpServlet {
    private static final String UPLOAD_DIR = "uploads";
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        String fileName = getFileName(filePart);
        File uploadFile = new File(getServletContext().getRealPath("") + File.separator + UPLOAD_DIR + File.separator + fileName);
        try (FileOutputStream fos = new FileOutputStream(uploadFile)) {
            byte[] buffer = new byte[1024];
            int length;
            InputStream is = filePart.getInputStream();
            while ((length = is.read(buffer)) > 0) {
                fos.write(buffer, 0, length);
            }
            saveToDatabase(fileName, uploadFile);
            response.sendRedirect("upload_success.jsp?filename=" + fileName);
        } catch (Exception e) {
            e.printStackTrace();
            response.sendRedirect("upload_error.jsp");
        }
    }

    private String getFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }

    private void saveToDatabase(String fileName, File file) throws Exception {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO pdf_files (file_name, file_path) VALUES (?, ?)")) {
            pstmt.setString(1, fileName);
            pstmt.setString(2, file.getAbsolutePath());
            pstmt.executeUpdate();
        }
    }
}