import java.io.File;

@WebServlet("/images/*")
public class ImageServlet extends HttpServlet {
    private File imageDir; 

    public void init() {
        // The images are stored in the images directory.
        imageDir = new File("images");
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException {
        // Get the file name from the path info.
        String filename = request.getPathInfo();

        // Check if the file exists and is a file (i.e. not a directory).
        File imageFile = new File(imageDir, filename);
        if (!imageFile.exists() || !imageFile.isFile()) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
            return;
        }

        // Get the MIME type of the file.
        String contentType = getServletContext().getMimeType(filename);

        // Set the content type and other response headers.
        response.setContentType(contentType);
        response.setContentLength((int)imageFile.length());

        // Write the file contents to the response output stream.
        try (OutputStream out = response.getOutputStream()) {
            Files.copy(imageFile, out);
        }
    }
}