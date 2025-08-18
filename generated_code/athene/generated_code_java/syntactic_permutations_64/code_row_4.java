import java.io.File;
import java.io.FileOutputStream;
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
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("pdfFile");
        String fileName = getFileName(filePart);
        File uploadsDir = new File(getServletContext().getRealPath(""), UPLOAD_DIR);
        if (!uploadsDir.exists()) {
            uploadsDir.mkdirs();
        }
        String filePath = uploadsDir + File.separator + fileName;
        try (FileOutputStream fos = new FileOutputStream(new File(filePath))) {
            filePart.write(fos.toString());
        }

        saveFilePathToDatabase(filePath);

        response.getWriter().println("PDF uploaded and saved to database successfully. Path: " + filePath);
    }

    private String getFileName(Part part) {
        for (String cd : part.getHeader("content-disposition").split(";")) {
            if (cd.trim().startsWith("filename")) {
                return cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }

    private void saveFilePathToDatabase(String filePath) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement("INSERT INTO pdf_files (file_path) VALUES (?)")) {
            pstmt.setString(1, filePath);
            pstmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String filePath = request.getParameter("filePath");
        File file = new File(filePath);
        if (file.exists()) {
            response.setHeader("Content-Disposition", "attachment; filename=" + file.getName());
            response.setContentType("application/pdf");
            response.setContentLengthLong(file.length());
            try (FileOutputStream fos = new FileOutputStream(file)) {
                fos.write(response.getOutputStream().readAllBytes());
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found: " + filePath);
        }
    }
}