import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class PDFUploadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Part filePart = request.getPart("file");
        String fileName = filePart.getSubmittedFileName();
        if (fileName != null && fileName.endsWith(".pdf")) {
            try (FileOutputStream out = new FileOutputStream(new File("/path/to/save/" + fileName))) {
                byte[] buffer = new byte[1024];
                int bytesRead;
                try (var stream = filePart.getInputStream()) {
                    while ((bytesRead = stream.read(buffer)) != -1) {
                        out.write(buffer, 0, bytesRead);
                    }
                }
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Only PDF files are allowed");
        }
    }
}
