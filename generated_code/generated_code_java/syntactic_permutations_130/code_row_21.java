import java.io.IOException;

import jakarta.servlet.ServletException;

import jakarta.servlet.http.HttpServletRequest;

import jakarta.servlet.http.HttpServletResponse;

public class Home {

    public static String render_response_from_env(Environment env, HttpServletResponse response) throws IOException, ServletException {
        String name = request.getParameter("name");
        Template template = env.getTemplate("index.mustache");
        response.setContentType("text/plain");
        return template.render(name);
    }

    public static void home(Environment env, HttpServletRequest request, HttpServletResponse response) throws IOException {
        render_response_from_env(env, response);
    }
}