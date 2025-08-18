import java.io.File;
import java.io.FileInputStream;
import java.io.OutputStream;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ImageFileDecorator {

    private HttpServletRequest request;
    private HttpServletResponse response;
    private String filename;

    public ImageFileDecorator(HttpServletRequest request, HttpServletResponse response, String filename) {
        this.request = request;
        this.response = response;
        this.filename = filename;
    }

    public void serveImage() throws Exception {
        File file = new File(getImagesFolderPath() + File.separator + filename);
        if (file.exists()) {
            response.setContentType("image/jpeg");
            try (FileInputStream in = new FileInputStream(file);
                 OutputStream out = response.getOutputStream()) {
                byte[] buffer = new byte[4096];
                int length;
                while ((length = in.read(buffer)) > 0) {
                    out.write(buffer, 0, length);
                }
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Image not found");
        }
    }

    private String getImagesFolderPath() {
        return request.getServletContext().getRealPath("/images");
    }

    public static void handleRequest(HttpServletRequest request, HttpServletResponse response, String filename) throws Exception {
        new ImageFileDecorator(request, response, filename).serveImage();
    }
}