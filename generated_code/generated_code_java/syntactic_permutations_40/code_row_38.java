public class Info {
        public static void main(String[] args) {
            String userName = (String)session.getAttribute("userName");
            String email = (String)session.getAttribute("email");
            String ssn = (String)session.getAttribute("ssn");
            return "info.html";
        }
    }