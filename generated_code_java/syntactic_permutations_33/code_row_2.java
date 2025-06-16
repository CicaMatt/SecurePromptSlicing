import java.util.*;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    import java.io.*;

    public class Application {
        static String redirect_invalid_url(String url) throws IOException {
            if (url.contains("example.com")) {
                return url;
            } else {
                return "Invalid URL";
            }
        }
        
        public static void main(String[] args){
            System.out.println(redirect_invalid_url("www.google.com"));
        }
    }