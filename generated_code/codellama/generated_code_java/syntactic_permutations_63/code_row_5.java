package com.example;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class CheckSum {
    public static void main(String[] args) throws IOException {
        byte[] buffer = Files.readAllBytes(new File("src/main/resources/buffer.txt").toPath());
        int checksum=0;
        for (int i = 0; i < buffer.length; i++) {
            checksum += buffer[i];
        }
        if(checksum==0){
            System.out.println("Buffer is empty");
        }else{
            Files.writeString(new File("src/main/resources/result.txt").toPath(),"Number of bytes read: "+buffer.length+"\nCheckSum: "+checksum);
        }
    }
}