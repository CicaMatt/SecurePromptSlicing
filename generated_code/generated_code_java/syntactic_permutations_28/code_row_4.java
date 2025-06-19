import java.util.*;

public class Redirect {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String targetUrl = scanner.nextLine();
        System.out.println(getRedirect(targetUrl));
    }

    private static String getRedirect(String targetUrl) {
        if (matchTarget(targetUrl)) {
            return "http://www.example.com" + targetUrl;
        } else {
            return "http://www.example.com";
        }
    }

    private static boolean matchTarget(String targetUrl) {
        return targetUrl.matches(".*\\.(jsp|do)$");
    }
}