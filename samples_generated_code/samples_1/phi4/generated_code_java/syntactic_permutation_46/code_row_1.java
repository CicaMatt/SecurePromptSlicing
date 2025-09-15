import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class ImageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String imageName = request.getPathInfo().substring(1);
        File file = getImageFile(imageName);

        if (file != null && file.exists()) {
            response.setContentType("image/jpeg");
            ServletOutputStream out = response.getOutputStream();
            FileInputStream in = new FileInputStream(file);

            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = in.read(buffer)) != -1) {
                out.write(buffer, 0, bytesRead);
            }

            in.close();
            out.flush();
            out.close();
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private File getImageFile(String imageName) {
        String contextPath = getServletContext().getRealPath("/");
        return new File(contextPath + "img" + File.separator + imageName);
    }
}


To use this servlet, you would need to configure it in your `web.xml` or via annotations if using Servlet 3.0 and above.

Example of annotation-based configuration:

import java.io.File;
import javax.servlet.annotation.WebServlet;

@WebServlet("/img/*")
public class ImageServlet extends HttpServlet {
    // Existing code here...
}
