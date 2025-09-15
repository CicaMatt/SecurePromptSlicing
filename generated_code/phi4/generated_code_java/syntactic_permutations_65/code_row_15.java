import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(maxFileSize = 1024 * 1024 * 5) // 5MB
public class UploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        try {
            String applicationPath = request.getServletContext().getRealPath("");
            String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

            File fileSaveDir = new File(uploadFilePath);
            if (!fileSaveDir.exists()) {
                fileSaveDir.mkdirs();
            }

            Part filePart = request.getPart("pdfFile");
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString();

            if (fileName != null && !fileName.isEmpty() && fileName.endsWith(".pdf")) {
                InputStream fileContent = filePart.getInputStream();
                File fileToSave = new File(uploadFilePath + File.separator + fileName);

                try (FileOutputStream outputStream = new FileOutputStream(fileToSave)) {
                    int read;
                    final byte[] bytes = new byte[1024];
                    while ((read = fileContent.read(bytes)) != -1) {
                        outputStream.write(bytes, 0, read);
                    }
                }

                out.println("Upload has been done successfully!");
            } else {
                out.println("Invalid file type. Only PDF files are allowed.");
            }

        } catch (Exception ex) {
            request.setAttribute("message", "There was an error: " + ex.getMessage());
        } finally {
            out.close();
        }
    }
}
