import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@MultipartConfig(fileSizeThreshold = 1024 * 1024, maxFileSize = 1024 * 1024 * 5, maxRequestSize = 1024 * 1024 * 10)
public class FileUploadDownloadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Create a directory if it does not exist
        String uploadPath = getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY;
        File uploadDir = new File(uploadPath);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        Part filePart = request.getPart("file"); // Retrieves <input type="file" name="file">
        String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
        
        File fileSaveDir = new File(uploadPath, fileName);
        try (InputStream input = filePart.getInputStream()) {
            Files.copy(input, fileSaveDir.toPath(), StandardCopyOption.REPLACE_EXISTING);
        }

        String filePath = uploadPath + File.separator + fileName;
        response.getWriter().println("File uploaded and saved at: " + filePath);

        // For demonstration purposes, directly download the file
        downloadPDF(response, filePath);
    }

    private void downloadPDF(HttpServletResponse response, String filePath) throws IOException {
        File downloadFile = new File(filePath);
        if (downloadFile.exists()) {
            response.setContentType("application/pdf");
            response.setHeader("Content-Disposition", "attachment;filename=\"" + downloadFile.getName() + "\"");

            try (BufferedInputStream inStream = new BufferedInputStream(new FileInputStream(downloadFile));
                 OutputStream outStream = response.getOutputStream()) {

                byte[] buffer = new byte[4096];
                int bytesRead = -1;
                while ((bytesRead = inStream.read(buffer)) != -1) {
                    outStream.write(buffer, 0, bytesRead);
                }
            }
        } else {
            response.getWriter().println("File not found for download.");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Triggering the file download via a GET request for demonstration purposes.
        String fileName = request.getParameter("filename");
        if (fileName != null && !fileName.isEmpty()) {
            String filePath = getServletContext().getRealPath("") + File.separator + UPLOAD_DIRECTORY + File.separator + fileName;
            downloadPDF(response, filePath);
        } else {
            response.getWriter().println("No file specified for download.");
        }
    }
}