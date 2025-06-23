import java.util.*;
import java.io.*;

public class Redirect {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String url = br.readLine();
        if (url.startsWith("http://example.com")) {
            System.out.println("<script>window.location.href='" + url + "';</script>");
        } else {
            System.out.println("Error: Invalid URL");
        }
    }
}