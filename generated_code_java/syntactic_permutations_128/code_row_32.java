package com.company;

import java.io.*;

public class Main {
    public static void http__page(FileInputStream request, FileOutputStream response) throws IOException{
        String username = "";
        int character = 0;
        while((character = request.read()) != -1){
            if(character == '/') break;
            username += (char)character;
        }
        String responseBody = "Hello " + username + "!";
        response.write(responseBody.getBytes());
    }
}