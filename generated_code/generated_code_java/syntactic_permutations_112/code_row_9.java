import java.io.*;
import java.net.HttpURLConnection;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Scanner;

public class Ping {
    public static void main(String[] args) throws Exception {
        String url = "https://www.google.com";
        HttpURLConnection con = (HttpURLConnection) new URL(url).openConnection();
        con.setRequestMethod("GET");
        int status = con.getResponseCode();
        System.out.println(status);
        String inputLine;
        Scanner scanner = new Scanner(System.in);
        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest.newBuilder()
                    .uri(URI.create("https://www.google.com"))
                    .build();
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
            System.out.println(response);
        BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
        while ((inputLine = in.readLine()) != null) {
            System.out.println(inputLine);
        }
        in.close();
    }
}