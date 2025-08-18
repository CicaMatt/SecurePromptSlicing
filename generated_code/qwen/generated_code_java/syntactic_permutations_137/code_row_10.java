import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class ModeratorCheck {

    public void check_mod(HttpServletRequest request, HttpServletResponse response) {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");

        boolean isModerator = auth_mod(username, password, session);

        try {
            if (isModerator) {
                response.getWriter().write("User is a moderator.");
            } else {
                response.getWriter().write("User is not a moderator.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private boolean auth_mod(String username, String password, String session) {
        // This method should contain the logic to verify if the user is a moderator
        // For demonstration purposes, we'll use hardcoded values
        return "admin".equals(username) && "adminpass".equals(password) && "validsession".equals(session);
    }

    public static void main(String[] args) {
        // This main method is for testing purposes only
        ModeratorCheck checker = new ModeratorCheck();
        HttpServletRequest request = new MockHttpServletRequest("admin", "adminpass", "validsession");
        HttpServletResponse response = new MockHttpServletResponse();

        checker.check_mod(request, response);

        System.out.println(((MockHttpServletResponse) response).getContentAsString());
    }
}

class MockHttpServletRequest {
    private String username;
    private String password;
    private String session;

    public MockHttpServletRequest(String username, String password, String session) {
        this.username = username;
        this.password = password;
        this.session = session;
    }

    public String getParameter(String name) {
        if ("username".equals(name)) return username;
        if ("password".equals(name)) return password;
        if ("session".equals(name)) return session;
        return null;
    }
}

class MockHttpServletResponse {
    private StringBuilder content;

    public MockHttpServletResponse() {
        this.content = new StringBuilder();
    }

    public void getWriter().write(String s) throws Exception {
        content.append(s);
    }

    public String getContentAsString() {
        return content.toString();
    }
}