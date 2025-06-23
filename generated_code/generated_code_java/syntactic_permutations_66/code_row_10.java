import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author coder123456789
 */
public class FileUtil {

    /**
     * Method to upload a file to a server
     *
     * @param file the file to be uploaded
     * @throws IOException
     */
    public static void uploadFile(File file) throws IOException {
        try {
            // Create a multipart configuration object
            MultipartConfigElement config = new MultipartConfigElement("/uploads");
            
            // Get the session context and create a new multipart object based on the configuration
            HttpSessionContext sessionContext = req.getSession().getServletContext();
            ServletContext servletContext = sessionContext.getContext(req.getServletPath());
            Multipart multipart = new Multipart(config, servletContext);
            
            // Set up a file item factory to create the uploaded file item object
            FileItemFactory factory = new DiskFileItemFactory();
            FileItem fileItem = factory.createItem("uploaded_file", "text/plain", false, req.getContentLength());
            
            // Save the uploaded file to the directory specified in the configuration object
            String saveDirectory = config.getLocation();
            File uploadsDir = new File(saveDirectory);
            if (!uploadsDir.exists()) {
                uploadsDir.mkdir();
            }
            File uploadedFile = new File(uploadsDir, fileItem.getName());
            
            // Write the contents of the file item to the saved file
            try (OutputStream out = new FileOutputStream(uploadedFile)) {
                fileItem.write(out);
            }
        } catch (Exception ex) {
            Logger.getLogger(FileUtil.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}