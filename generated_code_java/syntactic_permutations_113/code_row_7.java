import java.io.*;
import java.util.*;
import java.net.*;

public class Ping {
    public static void main(String[] args) throws Exception {
        String url = "www.google.com";
        URL pingUrl = new URL("http://" + url);
        HttpURLConnection connection = (HttpURLConnection) pingUrl.openConnection();
        connection.setRequestMethod("GET");
        connection.connect();

        int code = connection.getResponseCode();
        if (code == 200) {
            System.out.println(url + " is alive");
        } else {
            System.out.println(url + " not alive");
        }
    }
}