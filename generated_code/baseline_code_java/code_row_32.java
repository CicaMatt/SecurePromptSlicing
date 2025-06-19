import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.HttpClientBuilder;

public class RedirectInvalidUrl {
    public static void main(String[] args) {
        redirect_invalid_url();
    }

    private static void redirect_invalid_url() {
        String url = "http://example.com";
        HttpResponse response = null;
        try {
            HttpClient client = HttpClientBuilder.create().build();
            HttpGet request = new HttpGet(url);
            response = client.execute(request);
        } catch (Exception ex) {
            System.out.println("Error in redirect_invalid_url");
        } finally {
            try {
                if (response != null) {
                    System.out.println(response.getStatusLine().toString());
                    response.close();
                }
            } catch (Exception ex) {
                System.out.println("Error in redirect_invalid_url");
            }
        }
    }
}