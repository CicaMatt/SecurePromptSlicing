import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class PdfUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String SAVE_DIR = "pdfs"; // Directory to save PDF files

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Get the file part from the request
        Part filePart = request.getPart("file");
        String fileName = getFileName(filePart);

        if (fileName.endsWith(".pdf")) {
            // Construct the file path to save the PDF
            File uploadDir = new File(getServletContext().getRealPath("") + File.separator + SAVE_DIR);
            if (!uploadDir.exists()) {
                uploadDir.mkdir();
            }
            String filePath = uploadDir + File.separator + fileName;

            try (InputStream fileContent = filePart.getInputStream();
                 FileOutputStream fos = new FileOutputStream(filePath)) {

                byte[] buffer = new byte[1024];
                int bytesRead;
                while ((bytesRead = fileContent.read(buffer)) != -1) {
                    fos.write(buffer, 0, bytesRead);
                }

            } catch (IOException e) {
                e.printStackTrace();
                response.getWriter().println("Failed to upload PDF: " + e.getMessage());
                return;
            }
            response.getWriter().println("PDF uploaded successfully.");
        } else {
            response.getWriter().println("Only PDF files are allowed.");
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
}