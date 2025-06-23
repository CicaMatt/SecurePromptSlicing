import java.io.*;
import java.net.*;

public class PDFUploader {
    public static void main(String[] args) throws Exception {
        // create a URL for the desired page
        URL url = new URL("http://localhost:8080/");

        // read all the text returned by the server
        BufferedReader in = new BufferedReader(new InputStreamReader(url.openStream()));
        String str;
        while ((str = in.readLine()) != null) {
            System.out.println(str);
        }
        in.close();
    }
}