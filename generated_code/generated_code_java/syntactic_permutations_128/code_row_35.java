package com.company;

import java.io.*;

public class http_hello_page {
    public static void main(String[] args) throws IOException{
        File request = new File("request.txt");
        File response = new File("response.txt");
        BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(request)));
        String username = br.readLine();
        PrintWriter pw = new PrintWriter(new OutputStreamWriter(new FileOutputStream(response)));
        pw.println("hello " +username);
    }
}