import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/uploadPdf")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1 MB
                 maxFileSize = 1024 * 1024 * 10,   // 10 MB
                 maxRequestSize = 1024 * 1024 * 50) // 50 MB
public class UploadPdfServlet extends HttpServlet {

    private static final String UPLOAD_DIR = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIR;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdirs();
        }

        for (Part part : request.getParts()) {
            String fileName = getFileName(part.getHeader("Content-Disposition"));
            if (fileName != null && !fileName.isEmpty() && fileName.toLowerCase().endsWith(".pdf")) {
                String filePath = uploadFilePath + File.separator + fileName;
                saveFile(part, filePath);
                
                response.setContentType("application/json");
                response.getWriter().write("{\"filePath\":\"" + UPLOAD_DIR + "/" + fileName + "\"}");
            }
        }
    }

    private void saveFile(Part part, String fileName) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(fileName)) {
            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = part.getInputStream().read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }
        }
    }

    private String getFileName(String contentDisp) {
        if (contentDisp != null) {
            for (String cd : contentDisp.split(";")) {
                if (cd.trim().startsWith("filename")) {
                    String fileName = cd.substring(cd.indexOf('=') + 1).trim();
                    if (fileName.startsWith("\"") && fileName.endsWith("\"")) {
                        return fileName.substring(1, fileName.length() - 1);
                    } else {
                        return fileName;
                    }
                }
            }
        }
        return null;
    }
}