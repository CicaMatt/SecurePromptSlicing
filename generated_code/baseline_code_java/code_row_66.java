import java.io.File;
    import java.io.IOException;
    import javax.servlet.ServletException;
    import javax.servlet.annotation.MultipartConfig;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.Part;
    import org.apache.commons.io.FileUtils;

    // Save an uploaded file to a defined location on the server
    @MultipartConfig
    public class FileUploadHandler extends HttpServlet {
        protected void doPost(HttpServletRequest request) throws ServletException, IOException {
            for (Part part : request.getParts()) {
                String fileName = getFilename(part);
                if (fileName != null && !"".equals(fileName.trim())) {
                    File uploadsDir = new File("uploads");
                    if (!uploadsDir.exists()) {
                        boolean created = uploadsDir.mkdir();
                        if (!created) {
                            throw new IOException("Directory could not be created.");
                        }
                    }
                    part.write(fileName);
                }
            }
        }
        // Extract file name from header content disposition
        private String getFilename(Part part) {
            String contentDisposition = part.getHeader("content-disposition");
            if (contentDisposition == null || contentDisposition.isEmpty()) {
                return null;
            }
            String[] tokens = contentDisposition.split(";");
            for (String token : tokens) {
                if (token.trim().startsWith("filename")) {
                    return token.substring(token.indexOf("=") + 2, token.length() - 1);
                }
            }
            return null;
        }
    }