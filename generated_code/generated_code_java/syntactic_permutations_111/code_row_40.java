import java.net.MalformedURLException;
import java.net.URL;

public class ping {
    @Override
    public String toString() {
        try {
            URL url = new URL(request.getRequestURL().toString());
            Process process = Runtime.getRuntime().exec("ping -c 3 " + url.getHost());
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            int exitVal = process.waitFor();
            if (exitVal == 0) {
                return getUrl();
            } else {
                //abnormal...
            }
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}