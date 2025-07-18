package com.assignments.java;

public class http_hello_page {
    public static void main(String[] args) throws IOException {
        FileInputStream req = new FileInputStream("request.txt");
        BufferedReader reader = new BufferedReader(new InputStreamReader(req));
        String username = reader.readLine();
        FileOutputStream resp = new FileOutputStream("response.txt");
        PrintWriter writer = new PrintWriter(resp);
        writer.println("Hello "+username);
    }
}