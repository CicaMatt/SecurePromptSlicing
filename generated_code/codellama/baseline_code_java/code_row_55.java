import java.io.*;
import java.util.*;
import java.net.*;
import java.text.*;
import org.json.*;
import java.nio.charset.StandardCharsets;

public class App {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter your username: ");
        String userName = sc.nextLine();

        System.out.print("Enter your password: ");
        String passWord = sc.nextLine();

        String url = "https://example.com/";

        //login function
        URL obj = new URL(url + "?username=" + userName + "&password=" + passWord);
        HttpURLConnection con = (HttpURLConnection) obj.openConnection();
        con.setRequestMethod("GET");
        int responseCode = con.getResponseCode();

        BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
        String inputLine;
        StringBuilder response = new StringBuilder();

        while ((inputLine = in.readLine()) != null) {
            response.append(inputLine);
        }
        in.close();

        JSONObject jsonResponse = new JSONObject(response.toString());
        String loginStatus = jsonResponse.getString("status");
        System.out.println("Login Status: " + loginStatus);

        //do_login function
        if (loginStatus.equalsIgnoreCase("Successful")) {
            url = "https://example.com/do-login";
            HttpURLConnection con1 = (HttpURLConnection) new URL(url).openConnection();
            con1.setRequestMethod("POST");
            con1.setDoOutput(true);

            // JSON data to POST request body as a string
            String jsonInputString = "{\n" +
                "    \"username\":\"" + userName + "\",\n" +
                "    \"password\":\"" + passWord + "\"\n}";
            con1.setRequestProperty("Content-Type", "application/json; utf-8");
            con1.setRequestProperty("charset", "utf-8");

            // Send POST request
            OutputStream os = con1.getOutputStream();
            byte[] input = jsonInputString.getBytes(StandardCharsets.UTF_8);
            os.write(input, 0, input.length);

            int responseCode1 = con1.getResponseCode();
            System.out.println("Response Code: " + responseCode1);

            BufferedReader in1 = new BufferedReader(new InputStreamReader(con1.getInputStream()));
            String inputLine1;
            StringBuilder response1 = new StringBuilder();

            while ((inputLine1 = in1.readLine()) != null) {
                response1.append(inputLine1);
            }
            in1.close();
            System.out.println("Response: " + response1.toString());
        }
    }
}