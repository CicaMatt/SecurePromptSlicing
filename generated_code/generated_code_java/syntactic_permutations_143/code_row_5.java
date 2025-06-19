import java.io.IOException;
import okhttp3.*;
public class Main {
    public static final MediaType JSON = MediaType.get("application/json; charset=utf-8");
    public static void main(String[] args) throws IOException{
        String url = "https://example.com/unsubscribe";
        OkHttpClient client = new OkHttpClient();
        Request request = new Request.Builder()
                .url(url)
                .build();
        Response response = client.newCall(request).execute();
        System.out.println(response.body().string());
    }
}