import java.io.File;
import java.io.FileOutputStream;
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

@MultipartConfig
public class PdfUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";
    
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Get the uploaded file part from the request
        Part filePart = request.getPart("pdfFile");
        
        if (filePart != null) {
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();
            
            // Create uploads directory if it doesn't exist
            File uploadsDir = new File(UPLOAD_DIR);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }
            
            // Save the uploaded file in the uploads folder
            String filePath = UPLOAD_DIR + File.separator + fileName;
            try (FileOutputStream out = new FileOutputStream(new File(filePath))) {
                out.write(filePart.getInputStream().readAllBytes());
            }

            // Save file path to database
            saveFilePathToDatabase(fileName, filePath);

            response.getWriter().println("PDF uploaded successfully.");
        } else {
            response.getWriter().println("No PDF file found in the request.");
        }
    }

    private void saveFilePathToDatabase(String fileName, String filePath) {
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password")) {

            String sql = "INSERT INTO pdf_files (file_name, file_path) VALUES (?, ?)";
            
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, fileName);
                statement.setString(2, filePath);
                
                statement.executeUpdate();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws Exception {
        // Example usage
        File file = new File("path/to/your/test.pdf");
        PdfUploadServlet servlet = new PdfUploadServlet();

        HttpServletRequest request = null;  // Mock or use a testing framework to create a mock request
        HttpServletResponse response = null; // Mock or use a testing framework to create a mock response

        Part part = new Part() {
            @Override
            public String getContentType() { return "application/pdf"; }
            @Override
            public String getName() { return "pdfFile"; }
            @Override
            public String getSubmittedFileName() { return file.getName(); }

            @Override
            public java.io.InputStream getInputStream() throws IOException {
                return Files.newInputStream(Paths.get(file.toURI()));
            }
        };

        servlet.uploadPdf(request, response, part);
    }

    protected void uploadPdf(HttpServletRequest request, HttpServletResponse response, Part filePart) throws ServletException, IOException {
        doPost(request, response); // Simulate the POST action
    }
}


Note: Replace `"jdbc:mysql://localhost:3306/your_database"`, `"username"`, and `"password"` with your actual MySQL database connection details. Also, make sure to configure the necessary servlet mappings in your web.xml file or through annotations if needed.