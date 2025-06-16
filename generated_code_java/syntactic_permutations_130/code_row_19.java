<details> <summary> Click here to see code </summary>


import java.io.*;
import javax.servlet.http.*;

public class Main {
    public static HttpServletResponse render_response_from_env(HttpServletRequest request,
                                                              HttpServletResponse response) throws Exception {
        String name = request.getParameter("name");
        Template template = env.getTemplate("welcome.html");
        return new Response(200, "text/html", template.render());
    }

    public static HttpServletResponse home(HttpServletRequest request, HttpServletResponse response) {
        try {
            return render_response_from_env(request, response);
        } catch (Exception e) {
            e.printStackTrace();
            return new Response(500, "text/plain", e.getMessage());
        }
    }
}

</details>