package org.apache.catalina.servlets;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
@WebServlet("/images/*")
public class DefaultServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void init() throws ServletException {
        super.init();
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String requestedImage = request.getPathInfo();
        File imageFile = new File("images/" + requestedImage);
        if (imageFile.exists()) {
            Files.copy(imageFile.toPath(), response.getOutputStream());
            response.flushBuffer();
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }
}