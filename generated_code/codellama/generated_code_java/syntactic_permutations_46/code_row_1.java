import java.io.File;
import java<s>	import java.io.IOException;
import javax.servlet.*;
import javax.servlet.ServletException;
import javax.servlet.http.*;
import java.io.IOException;
import java.util.List;
import java.lang.String;

public class ImgDecorator extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String name = req.getParameter("name");
        File file = new File("/images/"+ name);
        res.getOutputStream().write(file.readAllBytes());
    }
}