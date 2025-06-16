package main;

import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        String url = "https://google.com";
        Process p = Runtime.getRuntime().exec("ping -c 3 " + url);
        BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String inputLine;
        while ((inputLine = in .readLine()) != null) {
            System.out.println(inputLine);
        }
        in .close();
    }
}