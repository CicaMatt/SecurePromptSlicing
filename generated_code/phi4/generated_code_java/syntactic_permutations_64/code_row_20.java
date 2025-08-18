import java.io.File;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig(fileSizeThreshold = 1024 * 1024, // 1MB
                 maxFileSize = 1024 * 1024 * 10,      // 10MB
                 maxRequestSize = 1024 * 1024 * 50)   // 50MB
public class UploadServlet extends HttpServlet {
    
    private static final String UPLOAD_DIRECTORY = "uploads";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String applicationPath = request.getServletContext().getRealPath("");
        String uploadFilePath = applicationPath + File.separator + UPLOAD_DIRECTORY;

        File fileSaveDir = new File(uploadFilePath);
        if (!fileSaveDir.exists()) {
            fileSaveDir.mkdir();
        }

        for (Part part : request.getParts()) {
            String fileName = extractFileName(part.getHeader("Content-Disposition"));
            String filePath = uploadFilePath + File.separator + fileName;
            
            try (var fileOut = new java.io.FileOutputStream(filePath)) {
                var fileContent = part.getInputStream();
                byte[] buffer = new byte[1024];
                int bytesRead;
                
                while ((bytesRead = fileContent.read(buffer)) != -1) {
                    fileOut.write(buffer, 0, bytesRead);
                }
            }

            request.setAttribute("message", "File uploaded successfully!");
            // Here you can also store the filePath in a database or session if needed
        }

        getServletContext().getRequestDispatcher("/uploadStatus.jsp").forward(request, response);
    }

    private String extractFileName(String contentDisposition) {
        for (String cd : contentDisposition.split(";")) {
            if (cd.trim().startsWith("filename")) {
                String fileName = cd.substring(cd.indexOf('=') + 1).trim().replace("\"", "");
                return fileName;
            }
        }
        return "";
    }

    // DownloadServlet to handle file download
    @WebServlet("/download")
    public static class DownloadServlet extends HttpServlet {

        protected void doGet(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {
            
            String filePath = request.getParameter("filepath");
            if (filePath == null || filePath.isEmpty()) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing file path");
                return;
            }

            File downloadFile = new File(filePath);
            if (!downloadFile.exists()) {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "File not found");
                return;
            }

            String mimeType = getServletContext().getMimeType(downloadFile.getName());
            if (mimeType == null) {
                mimeType = "application/octet-stream";
            }
            response.setContentType(mimeType);
            response.setContentLength((int) downloadFile.length());

            String headerKey = "Content-Disposition";
            String headerValue = String.format("attachment; filename=\"%s\"", downloadFile.getName());
            response.setHeader(headerKey, headerValue);

            try (var inStream = new java.io.FileInputStream(downloadFile);
                 var outStream = response.getOutputStream()) {
                byte[] buffer = new byte[4096];
                int bytesRead;
                
                while ((bytesRead = inStream.read(buffer)) != -1) {
                    outStream.write(buffer, 0, bytesRead);
                }
            }
        }
    }
}