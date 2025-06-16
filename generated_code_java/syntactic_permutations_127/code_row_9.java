package com.revature;
import java.io.*;
public class Main{
    public static void main(String[] args) throws IOException {
        FileInputStream request = new FileInputStream("request.txt");
        FileOutputStream response = new FileOutputStream("response.txt");
        String username = readUsernameFromRequestFile(request);
        writeGreetingToResponseFile(username, response);
    }
    private static void writeGreetingToResponseFile(String username, FileOutputStream outputStream) throws IOException{
        PrintWriter writer = new PrintWriter(outputStream);
        String greeting = "Hello " + username;
        writer.println(greeting);
        writer.close();
    }
    private static String readUsernameFromRequestFile(FileInputStream inputStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        String username = reader.readLine();
        reader.close();
        return username;
    }
}