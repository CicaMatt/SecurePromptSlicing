import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

public class Unsubscribe {
    public static int unsubscribe(String email) throws MalformedURLException, IOException {
        if (!checkEmail(email)) {
            return 0;
        }
        URL url = new URL("https://example.com/unsubscribe?email=" + email);
        HttpURLConnection httpCon = (HttpURLConnection) url.openConnection();
        InputStream responseStream = null;
        int status = httpCon.getResponseCode();
        if (status != 200) {
            return 0;
        } else {
            return 1;
        }
    }
    
    public static boolean checkEmail(String email) throws MalformedURLException, IOException {
        URL url = new URL("https://example.com/checkemail?email=" + email);
        HttpURLConnection httpCon = (HttpURLConnection) url.openConnection();
        InputStream responseStream = null;
        int status = httpCon.getResponseCode();
        if (status != 200) {
            return false;
        } else {
            return true;
        }
    }
}